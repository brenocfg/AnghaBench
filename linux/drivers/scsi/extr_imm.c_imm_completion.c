#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ this_residual; int ptr; TYPE_4__* buffer; int /*<<< orphan*/  buffers_residual; } ;
struct scsi_cmnd {unsigned char* cmnd; TYPE_2__ SCp; TYPE_1__* device; } ;
struct TYPE_13__ {unsigned short base; scalar_t__ rd; } ;
typedef  TYPE_3__ imm_struct ;
struct TYPE_14__ {scalar_t__ length; } ;
struct TYPE_11__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  DID_BUS_BUSY ; 
 int /*<<< orphan*/  DID_ERROR ; 
 scalar_t__ IMM_BURST_SIZE ; 
 unsigned char READ_10 ; 
 unsigned char READ_6 ; 
 unsigned char WRITE_10 ; 
 unsigned char WRITE_6 ; 
 TYPE_3__* imm_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imm_fail (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int imm_in (TYPE_3__*,int,int) ; 
 int imm_out (TYPE_3__*,int,int) ; 
 unsigned long jiffies ; 
 int r_str (unsigned short) ; 
 TYPE_4__* sg_next (TYPE_4__*) ; 
 int sg_virt (TYPE_4__*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  w_ctr (unsigned short,int) ; 

__attribute__((used)) static int imm_completion(struct scsi_cmnd *cmd)
{
	/* Return codes:
	 * -1     Error
	 *  0     Told to schedule
	 *  1     Finished data transfer
	 */
	imm_struct *dev = imm_dev(cmd->device->host);
	unsigned short ppb = dev->base;
	unsigned long start_jiffies = jiffies;

	unsigned char r, v;
	int fast, bulk, status;

	v = cmd->cmnd[0];
	bulk = ((v == READ_6) ||
		(v == READ_10) || (v == WRITE_6) || (v == WRITE_10));

	/*
	 * We only get here if the drive is ready to comunicate,
	 * hence no need for a full imm_wait.
	 */
	w_ctr(ppb, 0x0c);
	r = (r_str(ppb) & 0xb8);

	/*
	 * while (device is not ready to send status byte)
	 *     loop;
	 */
	while (r != (unsigned char) 0xb8) {
		/*
		 * If we have been running for more than a full timer tick
		 * then take a rest.
		 */
		if (time_after(jiffies, start_jiffies + 1))
			return 0;

		/*
		 * FAIL if:
		 * a) Drive status is screwy (!ready && !present)
		 * b) Drive is requesting/sending more data than expected
		 */
		if (((r & 0x88) != 0x88) || (cmd->SCp.this_residual <= 0)) {
			imm_fail(dev, DID_ERROR);
			return -1;	/* ERROR_RETURN */
		}
		/* determine if we should use burst I/O */
		if (dev->rd == 0) {
			fast = (bulk
				&& (cmd->SCp.this_residual >=
				    IMM_BURST_SIZE)) ? IMM_BURST_SIZE : 2;
			status = imm_out(dev, cmd->SCp.ptr, fast);
		} else {
			fast = (bulk
				&& (cmd->SCp.this_residual >=
				    IMM_BURST_SIZE)) ? IMM_BURST_SIZE : 1;
			status = imm_in(dev, cmd->SCp.ptr, fast);
		}

		cmd->SCp.ptr += fast;
		cmd->SCp.this_residual -= fast;

		if (!status) {
			imm_fail(dev, DID_BUS_BUSY);
			return -1;	/* ERROR_RETURN */
		}
		if (cmd->SCp.buffer && !cmd->SCp.this_residual) {
			/* if scatter/gather, advance to the next segment */
			if (cmd->SCp.buffers_residual--) {
				cmd->SCp.buffer = sg_next(cmd->SCp.buffer);
				cmd->SCp.this_residual =
				    cmd->SCp.buffer->length;
				cmd->SCp.ptr = sg_virt(cmd->SCp.buffer);

				/*
				 * Make sure that we transfer even number of bytes
				 * otherwise it makes imm_byte_out() messy.
				 */
				if (cmd->SCp.this_residual & 0x01)
					cmd->SCp.this_residual++;
			}
		}
		/* Now check to see if the drive is ready to comunicate */
		w_ctr(ppb, 0x0c);
		r = (r_str(ppb) & 0xb8);

		/* If not, drop back down to the scheduler and wait a timer tick */
		if (!(r & 0x80))
			return 0;
	}
	return 1;		/* FINISH_RETURN */
}