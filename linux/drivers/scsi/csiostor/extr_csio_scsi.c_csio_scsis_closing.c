#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct csio_scsim {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sm_list; } ;
struct csio_ioreq {TYPE_2__ sm; int /*<<< orphan*/  wr_status; int /*<<< orphan*/  drv_status; TYPE_1__* lnode; } ;
struct csio_hw {int dummy; } ;
typedef  enum csio_scsi_ev { ____Placeholder_csio_scsi_ev } csio_scsi_ev ;
struct TYPE_3__ {struct csio_hw* hwp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_DB_ASSERT (int) ; 
 int /*<<< orphan*/  CSIO_DEC_STATS (struct csio_scsim*,int /*<<< orphan*/ ) ; 
#define  CSIO_SCSIE_CLOSE 131 
#define  CSIO_SCSIE_CLOSED 130 
#define  CSIO_SCSIE_COMPLETED 129 
#define  CSIO_SCSIE_DRVCLEANUP 128 
 int /*<<< orphan*/  ECANCELED ; 
 int /*<<< orphan*/  FW_EINVAL ; 
 int /*<<< orphan*/  FW_HOSTERROR ; 
 int /*<<< orphan*/  FW_SCSI_CLOSE_REQUESTED ; 
 int /*<<< orphan*/  FW_SUCCESS ; 
 int /*<<< orphan*/  csio_dbg (struct csio_hw*,char*,...) ; 
 int /*<<< orphan*/  csio_fatal (struct csio_hw*,char*,struct csio_ioreq*) ; 
 struct csio_scsim* csio_hw_to_scsim (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_scsis_uninit ; 
 int /*<<< orphan*/  csio_set_state (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_active ; 

__attribute__((used)) static void
csio_scsis_closing(struct csio_ioreq *req, enum csio_scsi_ev evt)
{
	struct csio_hw *hw = req->lnode->hwp;
	struct csio_scsim *scm = csio_hw_to_scsim(hw);

	switch (evt) {
	case CSIO_SCSIE_COMPLETED:
		csio_dbg(hw,
			 "ioreq %p recvd cmpltd (wr_status:%d) "
			 "in closing st\n", req, req->wr_status);
		/*
		 * Use -ECANCELED to explicitly tell the CLOSED event that
		 * the original I/O was returned to driver by FW.
		 * We dont really care if the I/O was returned with success by
		 * FW (because the CLOSE and completion of the I/O crossed each
		 * other), or any other return value. Once we are in aborting
		 * state, the success or failure of the I/O is unimportant to
		 * us.
		 */
		req->drv_status = -ECANCELED;
		break;

	case CSIO_SCSIE_CLOSED:
		/*
		 * Check if original I/O WR completed before the Close
		 * completion.
		 */
		if (req->drv_status != -ECANCELED) {
			csio_fatal(hw,
				   "Close completed before original I/O,"
				   " req:%p\n", req);
			CSIO_DB_ASSERT(0);
		}

		/*
		 * Either close succeeded, or we issued close to FW at the
		 * same time FW compelted it to us. Either way, the I/O
		 * is closed.
		 */
		CSIO_DB_ASSERT((req->wr_status == FW_SUCCESS) ||
					(req->wr_status == FW_EINVAL));
		req->wr_status = FW_SCSI_CLOSE_REQUESTED;

		CSIO_DEC_STATS(scm, n_active);
		list_del_init(&req->sm.sm_list);
		csio_set_state(&req->sm, csio_scsis_uninit);
		break;

	case CSIO_SCSIE_CLOSE:
		break;

	case CSIO_SCSIE_DRVCLEANUP:
		req->wr_status = FW_HOSTERROR;
		CSIO_DEC_STATS(scm, n_active);
		csio_set_state(&req->sm, csio_scsis_uninit);
		break;

	default:
		csio_dbg(hw, "Unhandled event:%d sent to req:%p\n", evt, req);
		CSIO_DB_ASSERT(0);
	}
}