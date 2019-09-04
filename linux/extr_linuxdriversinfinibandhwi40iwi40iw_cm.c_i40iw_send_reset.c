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
struct i40iw_puda_buf {int dummy; } ;
struct i40iw_cm_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_TIMER_TYPE_SEND ; 
 int SET_ACK ; 
 int SET_RST ; 
 struct i40iw_puda_buf* i40iw_form_cm_frame (struct i40iw_cm_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*) ; 
 int i40iw_schedule_cm_timer (struct i40iw_cm_node*,struct i40iw_puda_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int i40iw_send_reset(struct i40iw_cm_node *cm_node)
{
	struct i40iw_puda_buf *sqbuf;
	int flags = SET_RST | SET_ACK;

	sqbuf = i40iw_form_cm_frame(cm_node, NULL, NULL, NULL, flags);
	if (!sqbuf) {
		i40iw_pr_err("no sqbuf\n");
		return -1;
	}

	return i40iw_schedule_cm_timer(cm_node, sqbuf, I40IW_TIMER_TYPE_SEND, 0, 1);
}