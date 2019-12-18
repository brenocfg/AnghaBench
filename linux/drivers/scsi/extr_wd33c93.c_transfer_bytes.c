#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wd33c93_regs ;
typedef  int /*<<< orphan*/  uchar ;
struct TYPE_9__ {unsigned long this_residual; unsigned long ptr; scalar_t__ phase; TYPE_4__* buffer; scalar_t__ buffers_residual; } ;
struct scsi_cmnd {TYPE_3__ SCp; TYPE_2__* device; } ;
struct WD33C93_hostdata {int* sync_xfer; int dma_mode; scalar_t__ level2; int /*<<< orphan*/  dma; int /*<<< orphan*/  state; int /*<<< orphan*/  dma_cnt; int /*<<< orphan*/  pio_cnt; scalar_t__ (* dma_setup ) (struct scsi_cmnd*,int) ;scalar_t__ no_dma; } ;
struct TYPE_10__ {unsigned long length; } ;
struct TYPE_8__ {size_t id; TYPE_1__* host; } ;
struct TYPE_7__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int CTRL_EDI ; 
 int CTRL_IDI ; 
 int /*<<< orphan*/  D_DMA_RUNNING ; 
 scalar_t__ L2_BASIC ; 
 scalar_t__ L2_DATA ; 
 int /*<<< orphan*/  S_RUNNING_LEVEL2 ; 
 int /*<<< orphan*/  WD_CMD_SEL_ATN_XFER ; 
 int /*<<< orphan*/  WD_CMD_TRANS_INFO ; 
 int /*<<< orphan*/  WD_COMMAND_PHASE ; 
 int /*<<< orphan*/  WD_CONTROL ; 
 int /*<<< orphan*/  WD_SYNCHRONOUS_TRANSFER ; 
 unsigned long read_wd33c93_count (int /*<<< orphan*/  const) ; 
 TYPE_4__* sg_next (TYPE_4__*) ; 
 unsigned long sg_virt (TYPE_4__*) ; 
 scalar_t__ stub1 (struct scsi_cmnd*,int) ; 
 int /*<<< orphan*/  transfer_pio (int /*<<< orphan*/  const,int /*<<< orphan*/ *,unsigned long,int,struct WD33C93_hostdata*) ; 
 int /*<<< orphan*/  write_wd33c93 (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_wd33c93_cmd (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_wd33c93_count (int /*<<< orphan*/  const,unsigned long) ; 

__attribute__((used)) static void
transfer_bytes(const wd33c93_regs regs, struct scsi_cmnd *cmd,
		int data_in_dir)
{
	struct WD33C93_hostdata *hostdata;
	unsigned long length;

	hostdata = (struct WD33C93_hostdata *) cmd->device->host->hostdata;

/* Normally, you'd expect 'this_residual' to be non-zero here.
 * In a series of scatter-gather transfers, however, this
 * routine will usually be called with 'this_residual' equal
 * to 0 and 'buffers_residual' non-zero. This means that a
 * previous transfer completed, clearing 'this_residual', and
 * now we need to setup the next scatter-gather buffer as the
 * source or destination for THIS transfer.
 */
	if (!cmd->SCp.this_residual && cmd->SCp.buffers_residual) {
		cmd->SCp.buffer = sg_next(cmd->SCp.buffer);
		--cmd->SCp.buffers_residual;
		cmd->SCp.this_residual = cmd->SCp.buffer->length;
		cmd->SCp.ptr = sg_virt(cmd->SCp.buffer);
	}
	if (!cmd->SCp.this_residual) /* avoid bogus setups */
		return;

	write_wd33c93(regs, WD_SYNCHRONOUS_TRANSFER,
		      hostdata->sync_xfer[cmd->device->id]);

/* 'hostdata->no_dma' is TRUE if we don't even want to try DMA.
 * Update 'this_residual' and 'ptr' after 'transfer_pio()' returns.
 */

	if (hostdata->no_dma || hostdata->dma_setup(cmd, data_in_dir)) {
#ifdef PROC_STATISTICS
		hostdata->pio_cnt++;
#endif
		transfer_pio(regs, (uchar *) cmd->SCp.ptr,
			     cmd->SCp.this_residual, data_in_dir, hostdata);
		length = cmd->SCp.this_residual;
		cmd->SCp.this_residual = read_wd33c93_count(regs);
		cmd->SCp.ptr += (length - cmd->SCp.this_residual);
	}

/* We are able to do DMA (in fact, the Amiga hardware is
 * already going!), so start up the wd33c93 in DMA mode.
 * We set 'hostdata->dma' = D_DMA_RUNNING so that when the
 * transfer completes and causes an interrupt, we're
 * reminded to tell the Amiga to shut down its end. We'll
 * postpone the updating of 'this_residual' and 'ptr'
 * until then.
 */

	else {
#ifdef PROC_STATISTICS
		hostdata->dma_cnt++;
#endif
		write_wd33c93(regs, WD_CONTROL, CTRL_IDI | CTRL_EDI | hostdata->dma_mode);
		write_wd33c93_count(regs, cmd->SCp.this_residual);

		if ((hostdata->level2 >= L2_DATA) ||
		    (hostdata->level2 == L2_BASIC && cmd->SCp.phase == 0)) {
			write_wd33c93(regs, WD_COMMAND_PHASE, 0x45);
			write_wd33c93_cmd(regs, WD_CMD_SEL_ATN_XFER);
			hostdata->state = S_RUNNING_LEVEL2;
		} else
			write_wd33c93_cmd(regs, WD_CMD_TRANS_INFO);

		hostdata->dma = D_DMA_RUNNING;
	}
}