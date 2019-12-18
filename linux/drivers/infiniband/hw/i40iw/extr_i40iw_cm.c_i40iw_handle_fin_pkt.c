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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  rcv_nxt; } ;
struct i40iw_cm_node {int state; TYPE_1__ tcp_cntxt; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_CM_EVENT_ABORTED ; 
 void* I40IW_CM_STATE_CLOSED ; 
 int I40IW_CM_STATE_CLOSING ; 
#define  I40IW_CM_STATE_ESTABLISHED 136 
#define  I40IW_CM_STATE_FIN_WAIT1 135 
#define  I40IW_CM_STATE_FIN_WAIT2 134 
 int I40IW_CM_STATE_LAST_ACK ; 
#define  I40IW_CM_STATE_MPAREJ_RCVD 133 
#define  I40IW_CM_STATE_MPAREQ_SENT 132 
#define  I40IW_CM_STATE_OFFLOADED 131 
#define  I40IW_CM_STATE_SYN_RCVD 130 
#define  I40IW_CM_STATE_SYN_SENT 129 
#define  I40IW_CM_STATE_TIME_WAIT 128 
 int /*<<< orphan*/  I40IW_TIMER_TYPE_CLOSE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40iw_cleanup_retrans_entry (struct i40iw_cm_node*) ; 
 int /*<<< orphan*/  i40iw_create_event (struct i40iw_cm_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*,struct i40iw_cm_node*,int) ; 
 int /*<<< orphan*/  i40iw_rem_ref_cm_node (struct i40iw_cm_node*) ; 
 int /*<<< orphan*/  i40iw_schedule_cm_timer (struct i40iw_cm_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_send_ack (struct i40iw_cm_node*) ; 
 int /*<<< orphan*/  i40iw_send_fin (struct i40iw_cm_node*) ; 
 int /*<<< orphan*/  i40iw_send_reset (struct i40iw_cm_node*) ; 

__attribute__((used)) static void i40iw_handle_fin_pkt(struct i40iw_cm_node *cm_node)
{
	u32 ret;

	switch (cm_node->state) {
	case I40IW_CM_STATE_SYN_RCVD:
	case I40IW_CM_STATE_SYN_SENT:
	case I40IW_CM_STATE_ESTABLISHED:
	case I40IW_CM_STATE_MPAREJ_RCVD:
		cm_node->tcp_cntxt.rcv_nxt++;
		i40iw_cleanup_retrans_entry(cm_node);
		cm_node->state = I40IW_CM_STATE_LAST_ACK;
		i40iw_send_fin(cm_node);
		break;
	case I40IW_CM_STATE_MPAREQ_SENT:
		i40iw_create_event(cm_node, I40IW_CM_EVENT_ABORTED);
		cm_node->tcp_cntxt.rcv_nxt++;
		i40iw_cleanup_retrans_entry(cm_node);
		cm_node->state = I40IW_CM_STATE_CLOSED;
		atomic_inc(&cm_node->ref_count);
		i40iw_send_reset(cm_node);
		break;
	case I40IW_CM_STATE_FIN_WAIT1:
		cm_node->tcp_cntxt.rcv_nxt++;
		i40iw_cleanup_retrans_entry(cm_node);
		cm_node->state = I40IW_CM_STATE_CLOSING;
		i40iw_send_ack(cm_node);
		/*
		 * Wait for ACK as this is simultaneous close.
		 * After we receive ACK, do not send anything.
		 * Just rm the node.
		 */
		break;
	case I40IW_CM_STATE_FIN_WAIT2:
		cm_node->tcp_cntxt.rcv_nxt++;
		i40iw_cleanup_retrans_entry(cm_node);
		cm_node->state = I40IW_CM_STATE_TIME_WAIT;
		i40iw_send_ack(cm_node);
		ret =
		    i40iw_schedule_cm_timer(cm_node, NULL, I40IW_TIMER_TYPE_CLOSE, 1, 0);
		if (ret)
			i40iw_pr_err("node %p state = %d\n", cm_node, cm_node->state);
		break;
	case I40IW_CM_STATE_TIME_WAIT:
		cm_node->tcp_cntxt.rcv_nxt++;
		i40iw_cleanup_retrans_entry(cm_node);
		cm_node->state = I40IW_CM_STATE_CLOSED;
		i40iw_rem_ref_cm_node(cm_node);
		break;
	case I40IW_CM_STATE_OFFLOADED:
	default:
		i40iw_pr_err("bad state node %p state = %d\n", cm_node, cm_node->state);
		break;
	}
}