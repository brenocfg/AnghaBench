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
struct scsi_tape {TYPE_3__* buffer; TYPE_2__* device; } ;
struct TYPE_6__ {int syscall_result; } ;
struct TYPE_5__ {TYPE_1__* request_queue; } ;
struct TYPE_4__ {int /*<<< orphan*/  rq_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int MAX_COMMAND_SIZE ; 
 unsigned char MODE_SENSE ; 
 unsigned char MODE_SENSE_OMIT_BDESCS ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 struct st_request* st_do_scsi (int /*<<< orphan*/ *,struct scsi_tape*,unsigned char*,unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  st_release_request (struct st_request*) ; 

__attribute__((used)) static int read_mode_page(struct scsi_tape *STp, int page, int omit_block_descs)
{
	unsigned char cmd[MAX_COMMAND_SIZE];
	struct st_request *SRpnt;

	memset(cmd, 0, MAX_COMMAND_SIZE);
	cmd[0] = MODE_SENSE;
	if (omit_block_descs)
		cmd[1] = MODE_SENSE_OMIT_BDESCS;
	cmd[2] = page;
	cmd[4] = 255;

	SRpnt = st_do_scsi(NULL, STp, cmd, cmd[4], DMA_FROM_DEVICE,
			   STp->device->request_queue->rq_timeout, 0, 1);
	if (SRpnt == NULL)
		return (STp->buffer)->syscall_result;

	st_release_request(SRpnt);

	return STp->buffer->syscall_result;
}