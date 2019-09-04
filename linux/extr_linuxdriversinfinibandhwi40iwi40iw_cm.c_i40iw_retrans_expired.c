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
struct iw_cm_id {int /*<<< orphan*/  (* rem_ref ) (struct iw_cm_id*) ;} ;
struct i40iw_cm_node {int state; int /*<<< orphan*/  ref_count; struct iw_cm_id* cm_id; } ;
typedef  enum i40iw_cm_node_state { ____Placeholder_i40iw_cm_node_state } i40iw_cm_node_state ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_CM_EVENT_ABORTED ; 
 int I40IW_CM_STATE_CLOSED ; 
#define  I40IW_CM_STATE_CLOSING 131 
#define  I40IW_CM_STATE_FIN_WAIT1 130 
#define  I40IW_CM_STATE_LAST_ACK 129 
#define  I40IW_CM_STATE_SYN_RCVD 128 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40iw_create_event (struct i40iw_cm_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_rem_ref_cm_node (struct i40iw_cm_node*) ; 
 int /*<<< orphan*/  i40iw_send_reset (struct i40iw_cm_node*) ; 
 int /*<<< orphan*/  stub1 (struct iw_cm_id*) ; 

__attribute__((used)) static void i40iw_retrans_expired(struct i40iw_cm_node *cm_node)
{
	struct iw_cm_id *cm_id = cm_node->cm_id;
	enum i40iw_cm_node_state state = cm_node->state;

	cm_node->state = I40IW_CM_STATE_CLOSED;
	switch (state) {
	case I40IW_CM_STATE_SYN_RCVD:
	case I40IW_CM_STATE_CLOSING:
		i40iw_rem_ref_cm_node(cm_node);
		break;
	case I40IW_CM_STATE_FIN_WAIT1:
	case I40IW_CM_STATE_LAST_ACK:
		if (cm_node->cm_id)
			cm_id->rem_ref(cm_id);
		i40iw_send_reset(cm_node);
		break;
	default:
		atomic_inc(&cm_node->ref_count);
		i40iw_send_reset(cm_node);
		i40iw_create_event(cm_node, I40IW_CM_EVENT_ABORTED);
		break;
	}
}