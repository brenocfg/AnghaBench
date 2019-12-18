#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_1__* device; scalar_t__ result; } ;
struct pqi_io_request {struct scsi_cmnd* scmd; int /*<<< orphan*/  io_complete_callback; } ;
struct pqi_ctrl_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  pqi_add_to_raid_bypass_retry_list (struct pqi_ctrl_info*,struct pqi_io_request*,int) ; 
 int /*<<< orphan*/  pqi_queued_raid_bypass_complete ; 
 int /*<<< orphan*/  pqi_schedule_bypass_retry (struct pqi_ctrl_info*) ; 
 struct pqi_ctrl_info* shost_to_hba (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pqi_queue_raid_bypass_retry(struct pqi_io_request *io_request)
{
	struct scsi_cmnd *scmd;
	struct pqi_ctrl_info *ctrl_info;

	io_request->io_complete_callback = pqi_queued_raid_bypass_complete;
	scmd = io_request->scmd;
	scmd->result = 0;
	ctrl_info = shost_to_hba(scmd->device->host);

	pqi_add_to_raid_bypass_retry_list(ctrl_info, io_request, false);
	pqi_schedule_bypass_retry(ctrl_info);
}