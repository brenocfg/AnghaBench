#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct scsi_cmnd {int dummy; } ;
struct pqi_io_request {int /*<<< orphan*/  context; int /*<<< orphan*/  (* io_complete_callback ) (struct pqi_io_request*,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * error_info; int /*<<< orphan*/  status; struct scsi_cmnd* scmd; int /*<<< orphan*/  refcount; } ;
struct pqi_ctrl_info {unsigned int max_io_slots; struct pqi_io_request* io_request_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  DID_NO_CONNECT ; 
 int /*<<< orphan*/  ENXIO ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pqi_ctrl_offline_raid_error_info ; 
 int /*<<< orphan*/  set_host_byte (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct pqi_io_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pqi_fail_all_outstanding_requests(struct pqi_ctrl_info *ctrl_info)
{
	unsigned int i;
	struct pqi_io_request *io_request;
	struct scsi_cmnd *scmd;

	for (i = 0; i < ctrl_info->max_io_slots; i++) {
		io_request = &ctrl_info->io_request_pool[i];
		if (atomic_read(&io_request->refcount) == 0)
			continue;

		scmd = io_request->scmd;
		if (scmd) {
			set_host_byte(scmd, DID_NO_CONNECT);
		} else {
			io_request->status = -ENXIO;
			io_request->error_info =
				&pqi_ctrl_offline_raid_error_info;
		}

		io_request->io_complete_callback(io_request,
			io_request->context);
	}
}