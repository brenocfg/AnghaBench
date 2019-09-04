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
struct i40iw_cm_node {int state; } ;

/* Variables and functions */
#define  I40IW_CM_STATE_ESTABLISHED 132 
#define  I40IW_CM_STATE_MPAREQ_SENT 131 
#define  I40IW_CM_STATE_OFFLOADED 130 
#define  I40IW_CM_STATE_SYN_RCVD 129 
#define  I40IW_CM_STATE_SYN_SENT 128 
 int /*<<< orphan*/  i40iw_active_open_err (struct i40iw_cm_node*,int) ; 
 int /*<<< orphan*/  i40iw_passive_open_err (struct i40iw_cm_node*,int) ; 

__attribute__((used)) static void i40iw_indicate_pkt_err(struct i40iw_cm_node *cm_node)
{
	switch (cm_node->state) {
	case I40IW_CM_STATE_SYN_SENT:
	case I40IW_CM_STATE_MPAREQ_SENT:
		i40iw_active_open_err(cm_node, true);
		break;
	case I40IW_CM_STATE_ESTABLISHED:
	case I40IW_CM_STATE_SYN_RCVD:
		i40iw_passive_open_err(cm_node, true);
		break;
	case I40IW_CM_STATE_OFFLOADED:
	default:
		break;
	}
}