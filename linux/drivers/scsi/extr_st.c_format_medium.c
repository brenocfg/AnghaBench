#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct st_request {int dummy; } ;
struct scsi_tape {int long_timeout; TYPE_3__* buffer; TYPE_2__* device; scalar_t__ immediate; } ;
struct TYPE_6__ {int syscall_result; } ;
struct TYPE_5__ {TYPE_1__* request_queue; } ;
struct TYPE_4__ {int rq_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBC_printk (struct scsi_tape*,char*) ; 
 int /*<<< orphan*/  DMA_NONE ; 
 unsigned char FORMAT_UNIT ; 
 int MAX_COMMAND_SIZE ; 
 int /*<<< orphan*/  MAX_RETRIES ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 struct st_request* st_do_scsi (int /*<<< orphan*/ *,struct scsi_tape*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int format_medium(struct scsi_tape *STp, int format)
{
	int result = 0;
	int timeout = STp->long_timeout;
	unsigned char scmd[MAX_COMMAND_SIZE];
	struct st_request *SRpnt;

	memset(scmd, 0, MAX_COMMAND_SIZE);
	scmd[0] = FORMAT_UNIT;
	scmd[2] = format;
	if (STp->immediate) {
		scmd[1] |= 1;		/* Don't wait for completion */
		timeout = STp->device->request_queue->rq_timeout;
	}
	DEBC_printk(STp, "Sending FORMAT MEDIUM\n");
	SRpnt = st_do_scsi(NULL, STp, scmd, 0, DMA_NONE,
			   timeout, MAX_RETRIES, 1);
	if (!SRpnt)
		result = STp->buffer->syscall_result;
	return result;
}