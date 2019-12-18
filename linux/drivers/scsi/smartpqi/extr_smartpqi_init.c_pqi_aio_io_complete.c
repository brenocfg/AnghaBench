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
struct pqi_io_request {int /*<<< orphan*/  status; struct scsi_cmnd* scmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DID_IMM_RETRY ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  pqi_free_io_request (struct pqi_io_request*) ; 
 int /*<<< orphan*/  pqi_queue_raid_bypass_retry (struct pqi_io_request*) ; 
 scalar_t__ pqi_raid_bypass_retry_needed (struct pqi_io_request*) ; 
 int /*<<< orphan*/  pqi_scsi_done (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  set_host_byte (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pqi_aio_io_complete(struct pqi_io_request *io_request,
	void *context)
{
	struct scsi_cmnd *scmd;

	scmd = io_request->scmd;
	scsi_dma_unmap(scmd);
	if (io_request->status == -EAGAIN)
		set_host_byte(scmd, DID_IMM_RETRY);
	else if (pqi_raid_bypass_retry_needed(io_request)) {
		pqi_queue_raid_bypass_retry(io_request);
		return;
	}
	pqi_free_io_request(io_request);
	pqi_scsi_done(scmd);
}