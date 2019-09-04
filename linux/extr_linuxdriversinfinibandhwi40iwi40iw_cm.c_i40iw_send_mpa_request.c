#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i40iw_puda_buf {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/ * addr; } ;
struct i40iw_cm_node {int /*<<< orphan*/  pdata; TYPE_1__ mpa_hdr; int /*<<< orphan*/  mpa_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_TIMER_TYPE_SEND ; 
 int /*<<< orphan*/  MPA_KEY_REQUEST ; 
 int /*<<< orphan*/  SET_ACK ; 
 int /*<<< orphan*/  i40iw_cm_build_mpa_frame (struct i40iw_cm_node*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct i40iw_puda_buf* i40iw_form_cm_frame (struct i40iw_cm_node*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*,...) ; 
 int i40iw_schedule_cm_timer (struct i40iw_cm_node*,struct i40iw_puda_buf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40iw_send_mpa_request(struct i40iw_cm_node *cm_node)
{
	struct i40iw_puda_buf *sqbuf;

	if (!cm_node) {
		i40iw_pr_err("cm_node == NULL\n");
		return -1;
	}

	cm_node->mpa_hdr.addr = &cm_node->mpa_frame;
	cm_node->mpa_hdr.size = i40iw_cm_build_mpa_frame(cm_node,
							 &cm_node->mpa_hdr,
							 MPA_KEY_REQUEST);
	if (!cm_node->mpa_hdr.size) {
		i40iw_pr_err("mpa size = %d\n", cm_node->mpa_hdr.size);
		return -1;
	}

	sqbuf = i40iw_form_cm_frame(cm_node,
				    NULL,
				    &cm_node->mpa_hdr,
				    &cm_node->pdata,
				    SET_ACK);
	if (!sqbuf) {
		i40iw_pr_err("sq_buf == NULL\n");
		return -1;
	}
	return i40iw_schedule_cm_timer(cm_node, sqbuf, I40IW_TIMER_TYPE_SEND, 1, 0);
}