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
typedef  int /*<<< orphan*/  u8 ;
struct iw_cm_id {int /*<<< orphan*/  (* rem_ref ) (struct iw_cm_id*) ;int /*<<< orphan*/  (* add_ref ) (struct iw_cm_id*) ;} ;
struct TYPE_2__ {scalar_t__ client; } ;
struct i40iw_cm_node {scalar_t__ state; struct iw_cm_id* cm_id; int /*<<< orphan*/  passive_state; TYPE_1__ tcp_cntxt; struct i40iw_cm_node* loopbackpartner; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNREFUSED ; 
 void* I40IW_CM_STATE_CLOSED ; 
 scalar_t__ I40IW_CM_STATE_CLOSING ; 
 scalar_t__ I40IW_CM_STATE_LISTENER_DESTROYED ; 
 int I40IW_SEND_RESET_EVENT ; 
 int /*<<< orphan*/  IW_CM_EVENT_CONNECT_REPLY ; 
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40iw_cleanup_retrans_entry (struct i40iw_cm_node*) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*) ; 
 int /*<<< orphan*/  i40iw_rem_ref_cm_node (struct i40iw_cm_node*) ; 
 int i40iw_send_cm_event (struct i40iw_cm_node*,struct iw_cm_id*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i40iw_send_mpa_reject (struct i40iw_cm_node*,void const*,int /*<<< orphan*/ ) ; 
 int i40iw_send_reset (struct i40iw_cm_node*) ; 
 int /*<<< orphan*/  stub1 (struct iw_cm_id*) ; 
 int /*<<< orphan*/  stub2 (struct iw_cm_id*) ; 

__attribute__((used)) static int i40iw_cm_reject(struct i40iw_cm_node *cm_node, const void *pdata, u8 plen)
{
	int ret = 0;
	int err;
	int passive_state;
	struct iw_cm_id *cm_id = cm_node->cm_id;
	struct i40iw_cm_node *loopback = cm_node->loopbackpartner;

	if (cm_node->tcp_cntxt.client)
		return ret;
	i40iw_cleanup_retrans_entry(cm_node);

	if (!loopback) {
		passive_state = atomic_add_return(1, &cm_node->passive_state);
		if (passive_state == I40IW_SEND_RESET_EVENT) {
			cm_node->state = I40IW_CM_STATE_CLOSED;
			i40iw_rem_ref_cm_node(cm_node);
		} else {
			if (cm_node->state == I40IW_CM_STATE_LISTENER_DESTROYED) {
				i40iw_rem_ref_cm_node(cm_node);
			} else {
				ret = i40iw_send_mpa_reject(cm_node, pdata, plen);
				if (ret) {
					cm_node->state = I40IW_CM_STATE_CLOSED;
					err = i40iw_send_reset(cm_node);
					if (err)
						i40iw_pr_err("send reset failed\n");
				} else {
					cm_id->add_ref(cm_id);
				}
			}
		}
	} else {
		cm_node->cm_id = NULL;
		if (cm_node->state == I40IW_CM_STATE_LISTENER_DESTROYED) {
			i40iw_rem_ref_cm_node(cm_node);
			i40iw_rem_ref_cm_node(loopback);
		} else {
			ret = i40iw_send_cm_event(loopback,
						  loopback->cm_id,
						  IW_CM_EVENT_CONNECT_REPLY,
						  -ECONNREFUSED);
			i40iw_rem_ref_cm_node(cm_node);
			loopback->state = I40IW_CM_STATE_CLOSING;

			cm_id = loopback->cm_id;
			i40iw_rem_ref_cm_node(loopback);
			cm_id->rem_ref(cm_id);
		}
	}

	return ret;
}