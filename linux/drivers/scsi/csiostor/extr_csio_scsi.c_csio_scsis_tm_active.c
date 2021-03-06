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
struct csio_ioreq {TYPE_2__ sm; int /*<<< orphan*/  wr_status; int /*<<< orphan*/  eq_idx; int /*<<< orphan*/  drv_status; TYPE_1__* lnode; } ;
struct csio_hw {int dummy; } ;
typedef  enum csio_scsi_ev { ____Placeholder_csio_scsi_ev } csio_scsi_ev ;
struct TYPE_3__ {struct csio_hw* hwp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_DB_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIO_DEC_STATS (struct csio_scsim*,int /*<<< orphan*/ ) ; 
#define  CSIO_SCSIE_ABORT 131 
#define  CSIO_SCSIE_CLOSE 130 
#define  CSIO_SCSIE_COMPLETED 129 
#define  CSIO_SCSIE_DRVCLEANUP 128 
 int /*<<< orphan*/  FW_HOSTERROR ; 
 int /*<<< orphan*/  SCSI_ABORT ; 
 int /*<<< orphan*/  SCSI_CLOSE ; 
 int /*<<< orphan*/  csio_dbg (struct csio_hw*,char*,int,struct csio_ioreq*) ; 
 struct csio_scsim* csio_hw_to_scsim (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_scsi_abrt_cls (struct csio_ioreq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_scsis_aborting ; 
 int /*<<< orphan*/  csio_scsis_closing ; 
 int /*<<< orphan*/  csio_scsis_uninit ; 
 int /*<<< orphan*/  csio_set_state (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_wr_issue (struct csio_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_tm_active ; 

__attribute__((used)) static void
csio_scsis_tm_active(struct csio_ioreq *req, enum csio_scsi_ev evt)
{
	struct csio_hw *hw = req->lnode->hwp;
	struct csio_scsim *scm = csio_hw_to_scsim(hw);

	switch (evt) {
	case CSIO_SCSIE_COMPLETED:
		CSIO_DEC_STATS(scm, n_tm_active);
		list_del_init(&req->sm.sm_list);
		csio_set_state(&req->sm, csio_scsis_uninit);

		break;

	case CSIO_SCSIE_ABORT:
		csio_scsi_abrt_cls(req, SCSI_ABORT);
		if (req->drv_status == 0) {
			csio_wr_issue(hw, req->eq_idx, false);
			csio_set_state(&req->sm, csio_scsis_aborting);
		}
		break;


	case CSIO_SCSIE_CLOSE:
		csio_scsi_abrt_cls(req, SCSI_CLOSE);
		if (req->drv_status == 0) {
			csio_wr_issue(hw, req->eq_idx, false);
			csio_set_state(&req->sm, csio_scsis_closing);
		}
		break;

	case CSIO_SCSIE_DRVCLEANUP:
		req->wr_status = FW_HOSTERROR;
		CSIO_DEC_STATS(scm, n_tm_active);
		csio_set_state(&req->sm, csio_scsis_uninit);
		break;

	default:
		csio_dbg(hw, "Unhandled event:%d sent to req:%p\n", evt, req);
		CSIO_DB_ASSERT(0);
	}
}