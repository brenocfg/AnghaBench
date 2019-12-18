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
struct i40iw_qp {int iwarp_state; int /*<<< orphan*/  sc_qp; int /*<<< orphan*/  cm_node; } ;
struct i40iw_modify_qp_info {int next_iwarp_state; } ;
struct i40iw_gen_ae_info {int /*<<< orphan*/  ae_source; int /*<<< orphan*/  ae_code; } ;
struct i40iw_device {int /*<<< orphan*/  cqp; } ;
struct TYPE_4__ {uintptr_t scratch; int /*<<< orphan*/ * qp; struct i40iw_modify_qp_info info; } ;
struct TYPE_5__ {TYPE_1__ qp_modify; } ;
struct TYPE_6__ {TYPE_2__ u; } ;
struct cqp_commands_info {int post_sq; TYPE_3__ in; int /*<<< orphan*/  cqp_cmd; } ;
struct i40iw_cqp_request {struct cqp_commands_info info; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_AE_BAD_CLOSE ; 
#define  I40IW_QP_STATE_CLOSING 132 
#define  I40IW_QP_STATE_ERROR 131 
#define  I40IW_QP_STATE_IDLE 130 
#define  I40IW_QP_STATE_RTS 129 
#define  I40IW_QP_STATE_TERMINATE 128 
 int /*<<< orphan*/  OP_QP_MODIFY ; 
 int /*<<< orphan*/  i40iw_gen_ae (struct i40iw_device*,int /*<<< orphan*/ *,struct i40iw_gen_ae_info*,int) ; 
 struct i40iw_cqp_request* i40iw_get_cqp_request (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i40iw_handle_cqp_op (struct i40iw_device*,struct i40iw_cqp_request*) ; 
 int /*<<< orphan*/  i40iw_send_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct i40iw_modify_qp_info*,struct i40iw_modify_qp_info*,int) ; 

void i40iw_hw_modify_qp(struct i40iw_device *iwdev, struct i40iw_qp *iwqp,
			struct i40iw_modify_qp_info *info, bool wait)
{
	struct i40iw_cqp_request *cqp_request;
	struct cqp_commands_info *cqp_info;
	struct i40iw_modify_qp_info *m_info;
	struct i40iw_gen_ae_info ae_info;

	cqp_request = i40iw_get_cqp_request(&iwdev->cqp, wait);
	if (!cqp_request)
		return;

	cqp_info = &cqp_request->info;
	m_info = &cqp_info->in.u.qp_modify.info;
	memcpy(m_info, info, sizeof(*m_info));
	cqp_info->cqp_cmd = OP_QP_MODIFY;
	cqp_info->post_sq = 1;
	cqp_info->in.u.qp_modify.qp = &iwqp->sc_qp;
	cqp_info->in.u.qp_modify.scratch = (uintptr_t)cqp_request;
	if (!i40iw_handle_cqp_op(iwdev, cqp_request))
		return;

	switch (m_info->next_iwarp_state) {
	case I40IW_QP_STATE_RTS:
		if (iwqp->iwarp_state == I40IW_QP_STATE_IDLE)
			i40iw_send_reset(iwqp->cm_node);
		/* fall through */
	case I40IW_QP_STATE_IDLE:
	case I40IW_QP_STATE_TERMINATE:
	case I40IW_QP_STATE_CLOSING:
		ae_info.ae_code = I40IW_AE_BAD_CLOSE;
		ae_info.ae_source = 0;
		i40iw_gen_ae(iwdev, &iwqp->sc_qp, &ae_info, false);
		break;
	case I40IW_QP_STATE_ERROR:
	default:
		break;
	}
}