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
struct i40iw_sc_vsi {int /*<<< orphan*/  ilq; } ;
struct i40iw_puda_buf {int dummy; } ;
struct i40iw_cm_node {TYPE_1__* iwdev; } ;
struct TYPE_2__ {struct i40iw_sc_vsi vsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_ACK ; 
 struct i40iw_puda_buf* i40iw_form_cm_frame (struct i40iw_cm_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*) ; 
 int /*<<< orphan*/  i40iw_puda_send_buf (int /*<<< orphan*/ ,struct i40iw_puda_buf*) ; 

__attribute__((used)) static void i40iw_send_ack(struct i40iw_cm_node *cm_node)
{
	struct i40iw_puda_buf *sqbuf;
	struct i40iw_sc_vsi *vsi = &cm_node->iwdev->vsi;

	sqbuf = i40iw_form_cm_frame(cm_node, NULL, NULL, NULL, SET_ACK);
	if (sqbuf)
		i40iw_puda_send_buf(vsi->ilq, sqbuf);
	else
		i40iw_pr_err("no sqbuf\n");
}