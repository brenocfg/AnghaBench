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
struct siw_qp_attrs {size_t state; } ;
struct TYPE_2__ {size_t state; } ;
struct siw_qp {TYPE_1__ attrs; } ;
typedef  enum siw_qp_attr_mask { ____Placeholder_siw_qp_attr_mask } siw_qp_attr_mask ;

/* Variables and functions */
 int SIW_QP_ATTR_STATE ; 
#define  SIW_QP_STATE_CLOSING 132 
#define  SIW_QP_STATE_IDLE 131 
#define  SIW_QP_STATE_RTR 130 
#define  SIW_QP_STATE_RTS 129 
#define  SIW_QP_STATE_TERMINATE 128 
 int /*<<< orphan*/  siw_dbg_qp (struct siw_qp*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siw_qp_cm_drop (struct siw_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siw_qp_modify_nonstate (struct siw_qp*,struct siw_qp_attrs*,int) ; 
 int /*<<< orphan*/  siw_qp_nextstate_from_close (struct siw_qp*,struct siw_qp_attrs*) ; 
 int siw_qp_nextstate_from_idle (struct siw_qp*,struct siw_qp_attrs*,int) ; 
 int siw_qp_nextstate_from_rts (struct siw_qp*,struct siw_qp_attrs*) ; 
 int /*<<< orphan*/  siw_qp_nextstate_from_term (struct siw_qp*,struct siw_qp_attrs*) ; 
 int /*<<< orphan*/ * siw_qp_state_to_string ; 

int siw_qp_modify(struct siw_qp *qp, struct siw_qp_attrs *attrs,
		  enum siw_qp_attr_mask mask)
{
	int drop_conn = 0, rv = 0;

	if (!mask)
		return 0;

	siw_dbg_qp(qp, "state: %s => %s\n",
		   siw_qp_state_to_string[qp->attrs.state],
		   siw_qp_state_to_string[attrs->state]);

	if (mask != SIW_QP_ATTR_STATE)
		siw_qp_modify_nonstate(qp, attrs, mask);

	if (!(mask & SIW_QP_ATTR_STATE))
		return 0;

	switch (qp->attrs.state) {
	case SIW_QP_STATE_IDLE:
	case SIW_QP_STATE_RTR:
		rv = siw_qp_nextstate_from_idle(qp, attrs, mask);
		break;

	case SIW_QP_STATE_RTS:
		drop_conn = siw_qp_nextstate_from_rts(qp, attrs);
		break;

	case SIW_QP_STATE_TERMINATE:
		siw_qp_nextstate_from_term(qp, attrs);
		break;

	case SIW_QP_STATE_CLOSING:
		siw_qp_nextstate_from_close(qp, attrs);
		break;
	default:
		break;
	}
	if (drop_conn)
		siw_qp_cm_drop(qp, 0);

	return rv;
}