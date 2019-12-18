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
struct scsi_tape {int long_timeout; TYPE_3__* buffer; TYPE_2__* device; } ;
struct TYPE_6__ {int* b_data; int syscall_result; } ;
struct TYPE_5__ {TYPE_1__* request_queue; } ;
struct TYPE_4__ {int rq_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int MAX_COMMAND_SIZE ; 
 int MH_BIT_WP ; 
 size_t MH_OFF_BDESCS_LENGTH ; 
 size_t MH_OFF_DATA_LENGTH ; 
 size_t MH_OFF_DEV_SPECIFIC ; 
 size_t MH_OFF_MEDIUM_TYPE ; 
 int MODE_HEADER_LENGTH ; 
 unsigned char MODE_SELECT ; 
 unsigned char MODE_SELECT_PAGE_FORMAT ; 
 int MP_MSK_PAGE_NBR ; 
 int MP_OFF_PAGE_LENGTH ; 
 int MP_OFF_PAGE_NBR ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 struct st_request* st_do_scsi (int /*<<< orphan*/ *,struct scsi_tape*,unsigned char*,unsigned char,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  st_release_request (struct st_request*) ; 

__attribute__((used)) static int write_mode_page(struct scsi_tape *STp, int page, int slow)
{
	int pgo;
	unsigned char cmd[MAX_COMMAND_SIZE];
	struct st_request *SRpnt;
	int timeout;

	memset(cmd, 0, MAX_COMMAND_SIZE);
	cmd[0] = MODE_SELECT;
	cmd[1] = MODE_SELECT_PAGE_FORMAT;
	pgo = MODE_HEADER_LENGTH + (STp->buffer)->b_data[MH_OFF_BDESCS_LENGTH];
	cmd[4] = pgo + (STp->buffer)->b_data[pgo + MP_OFF_PAGE_LENGTH] + 2;

	/* Clear reserved fields */
	(STp->buffer)->b_data[MH_OFF_DATA_LENGTH] = 0;
	(STp->buffer)->b_data[MH_OFF_MEDIUM_TYPE] = 0;
	(STp->buffer)->b_data[MH_OFF_DEV_SPECIFIC] &= ~MH_BIT_WP;
	(STp->buffer)->b_data[pgo + MP_OFF_PAGE_NBR] &= MP_MSK_PAGE_NBR;

	timeout = slow ?
		STp->long_timeout : STp->device->request_queue->rq_timeout;
	SRpnt = st_do_scsi(NULL, STp, cmd, cmd[4], DMA_TO_DEVICE,
			   timeout, 0, 1);
	if (SRpnt == NULL)
		return (STp->buffer)->syscall_result;

	st_release_request(SRpnt);

	return STp->buffer->syscall_result;
}