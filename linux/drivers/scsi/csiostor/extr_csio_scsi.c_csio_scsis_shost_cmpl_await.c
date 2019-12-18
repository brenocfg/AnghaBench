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
struct csio_ioreq {TYPE_1__* lnode; int /*<<< orphan*/  sm; int /*<<< orphan*/  drv_status; } ;
typedef  enum csio_scsi_ev { ____Placeholder_csio_scsi_ev } csio_scsi_ev ;
struct TYPE_2__ {int /*<<< orphan*/  hwp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_DB_ASSERT (int /*<<< orphan*/ ) ; 
#define  CSIO_SCSIE_ABORT 130 
#define  CSIO_SCSIE_CLOSE 129 
#define  CSIO_SCSIE_DRVCLEANUP 128 
 int /*<<< orphan*/  csio_dbg (int /*<<< orphan*/ ,char*,int,struct csio_ioreq*) ; 
 int /*<<< orphan*/  csio_scsis_uninit ; 
 int /*<<< orphan*/  csio_set_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
csio_scsis_shost_cmpl_await(struct csio_ioreq *req, enum csio_scsi_ev evt)
{
	switch (evt) {
	case CSIO_SCSIE_ABORT:
	case CSIO_SCSIE_CLOSE:
		/*
		 * Just succeed the abort request, and hope that
		 * the remote device unregister path will cleanup
		 * this I/O to the upper layer within a sane
		 * amount of time.
		 */
		/*
		 * A close can come in during a LINK DOWN. The FW would have
		 * returned us the I/O back, but not the remote device lost
		 * FW event. In this interval, if the I/O times out at the upper
		 * layer, a close can come in. Take the same action as abort:
		 * return success, and hope that the remote device unregister
		 * path will cleanup this I/O. If the FW still doesnt send
		 * the msg, the close times out, and the upper layer resorts
		 * to the next level of error recovery.
		 */
		req->drv_status = 0;
		break;
	case CSIO_SCSIE_DRVCLEANUP:
		csio_set_state(&req->sm, csio_scsis_uninit);
		break;
	default:
		csio_dbg(req->lnode->hwp, "Unhandled event:%d sent to req:%p\n",
			 evt, req);
		CSIO_DB_ASSERT(0);
	}
}