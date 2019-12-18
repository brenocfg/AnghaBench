#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int /*<<< orphan*/  payload_len; } ;
struct TYPE_8__ {int /*<<< orphan*/  payload_len; } ;
struct bsg_job {TYPE_3__ reply_payload; TYPE_2__ request_payload; } ;
struct bfad_s {int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/  bfa; } ;
struct bfad_fcxp {int /*<<< orphan*/  bfa_rport; struct bfa_fcxp_s* bfa_fcxp; int /*<<< orphan*/  num_rsp_sgles; int /*<<< orphan*/  num_req_sgles; TYPE_1__* port; } ;
struct bfa_fcxp_s {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  s_id; } ;
struct TYPE_10__ {int /*<<< orphan*/  tsecs; TYPE_6__ fchs; int /*<<< orphan*/  cos; int /*<<< orphan*/  cts; int /*<<< orphan*/  vf_id; } ;
typedef  TYPE_4__ bfa_bsg_fcpt_t ;
struct TYPE_7__ {struct bfad_s* bfad; } ;

/* Variables and functions */
 int BFA_STATUS_ENOMEM ; 
 int BFA_STATUS_OK ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 struct bfa_fcxp_s* bfa_fcxp_req_rsp_alloc (struct bfad_fcxp*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcxp_send (struct bfa_fcxp_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,struct bfad_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_lps_get_tag_from_pid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfad_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfad_fcxp_get_req_sgaddr_cb ; 
 int /*<<< orphan*/  bfad_fcxp_get_req_sglen_cb ; 
 int /*<<< orphan*/  bfad_fcxp_get_rsp_sgaddr_cb ; 
 int /*<<< orphan*/  bfad_fcxp_get_rsp_sglen_cb ; 
 int /*<<< orphan*/  bfad_send_fcpt_cb ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
bfad_fcxp_bsg_send(struct bsg_job *job, struct bfad_fcxp *drv_fcxp,
		   bfa_bsg_fcpt_t *bsg_fcpt)
{
	struct bfa_fcxp_s *hal_fcxp;
	struct bfad_s	*bfad = drv_fcxp->port->bfad;
	unsigned long	flags;
	uint8_t	lp_tag;

	spin_lock_irqsave(&bfad->bfad_lock, flags);

	/* Allocate bfa_fcxp structure */
	hal_fcxp = bfa_fcxp_req_rsp_alloc(drv_fcxp, &bfad->bfa,
				  drv_fcxp->num_req_sgles,
				  drv_fcxp->num_rsp_sgles,
				  bfad_fcxp_get_req_sgaddr_cb,
				  bfad_fcxp_get_req_sglen_cb,
				  bfad_fcxp_get_rsp_sgaddr_cb,
				  bfad_fcxp_get_rsp_sglen_cb, BFA_TRUE);
	if (!hal_fcxp) {
		bfa_trc(bfad, 0);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		return BFA_STATUS_ENOMEM;
	}

	drv_fcxp->bfa_fcxp = hal_fcxp;

	lp_tag = bfa_lps_get_tag_from_pid(&bfad->bfa, bsg_fcpt->fchs.s_id);

	bfa_fcxp_send(hal_fcxp, drv_fcxp->bfa_rport, bsg_fcpt->vf_id, lp_tag,
		      bsg_fcpt->cts, bsg_fcpt->cos,
		      job->request_payload.payload_len,
		      &bsg_fcpt->fchs, bfad_send_fcpt_cb, bfad,
		      job->reply_payload.payload_len, bsg_fcpt->tsecs);

	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	return BFA_STATUS_OK;
}