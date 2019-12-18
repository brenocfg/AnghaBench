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
struct i40iw_puda_buf {int dummy; } ;
struct i40iw_cm_node {int state; int mpa_frame_rev; TYPE_1__* cm_id; int /*<<< orphan*/  passive_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rem_ref ) (TYPE_1__*) ;} ;

/* Variables and functions */
#define  I40IW_CM_STATE_CLOSED 141 
#define  I40IW_CM_STATE_ESTABLISHED 140 
#define  I40IW_CM_STATE_FIN_WAIT1 139 
#define  I40IW_CM_STATE_FIN_WAIT2 138 
#define  I40IW_CM_STATE_LAST_ACK 137 
#define  I40IW_CM_STATE_LISTENING 136 
#define  I40IW_CM_STATE_MPAREQ_RCVD 135 
#define  I40IW_CM_STATE_MPAREQ_SENT 134 
#define  I40IW_CM_STATE_OFFLOADED 133 
#define  I40IW_CM_STATE_SYN_RCVD 132 
#define  I40IW_CM_STATE_SYN_SENT 131 
#define  I40IW_CM_STATE_TIME_WAIT 130 
#define  IETF_MPA_V1 129 
#define  IETF_MPA_V2 128 
 int /*<<< orphan*/  atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40iw_active_open_err (struct i40iw_cm_node*,int) ; 
 int /*<<< orphan*/  i40iw_cleanup_retrans_entry (struct i40iw_cm_node*) ; 
 int /*<<< orphan*/  i40iw_passive_open_err (struct i40iw_cm_node*,int) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*,int) ; 
 int /*<<< orphan*/  i40iw_rem_ref_cm_node (struct i40iw_cm_node*) ; 
 int /*<<< orphan*/  i40iw_send_syn (struct i40iw_cm_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void i40iw_handle_rst_pkt(struct i40iw_cm_node *cm_node,
				 struct i40iw_puda_buf *rbuf)
{
	i40iw_cleanup_retrans_entry(cm_node);
	switch (cm_node->state) {
	case I40IW_CM_STATE_SYN_SENT:
	case I40IW_CM_STATE_MPAREQ_SENT:
		switch (cm_node->mpa_frame_rev) {
		case IETF_MPA_V2:
			cm_node->mpa_frame_rev = IETF_MPA_V1;
			/* send a syn and goto syn sent state */
			cm_node->state = I40IW_CM_STATE_SYN_SENT;
			if (i40iw_send_syn(cm_node, 0))
				i40iw_active_open_err(cm_node, false);
			break;
		case IETF_MPA_V1:
		default:
			i40iw_active_open_err(cm_node, false);
			break;
		}
		break;
	case I40IW_CM_STATE_MPAREQ_RCVD:
		atomic_add_return(1, &cm_node->passive_state);
		break;
	case I40IW_CM_STATE_ESTABLISHED:
	case I40IW_CM_STATE_SYN_RCVD:
	case I40IW_CM_STATE_LISTENING:
		i40iw_pr_err("Bad state state = %d\n", cm_node->state);
		i40iw_passive_open_err(cm_node, false);
		break;
	case I40IW_CM_STATE_OFFLOADED:
		i40iw_active_open_err(cm_node, false);
		break;
	case I40IW_CM_STATE_CLOSED:
		break;
	case I40IW_CM_STATE_FIN_WAIT2:
	case I40IW_CM_STATE_FIN_WAIT1:
	case I40IW_CM_STATE_LAST_ACK:
		cm_node->cm_id->rem_ref(cm_node->cm_id);
		/* fall through */
	case I40IW_CM_STATE_TIME_WAIT:
		cm_node->state = I40IW_CM_STATE_CLOSED;
		i40iw_rem_ref_cm_node(cm_node);
		break;
	default:
		break;
	}
}