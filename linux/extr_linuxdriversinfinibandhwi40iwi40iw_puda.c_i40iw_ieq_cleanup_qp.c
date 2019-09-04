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
struct list_head {int dummy; } ;
struct i40iw_pfpdu {int /*<<< orphan*/  mode; struct list_head rxlist; } ;
struct i40iw_sc_qp {struct i40iw_pfpdu pfpdu; } ;
struct i40iw_puda_rsrc {int dummy; } ;
struct i40iw_puda_buf {int dummy; } ;

/* Variables and functions */
 struct i40iw_puda_buf* i40iw_puda_get_listbuf (struct list_head*) ; 
 int /*<<< orphan*/  i40iw_puda_ret_bufpool (struct i40iw_puda_rsrc*,struct i40iw_puda_buf*) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 

void i40iw_ieq_cleanup_qp(struct i40iw_puda_rsrc *ieq, struct i40iw_sc_qp *qp)
{
	struct i40iw_puda_buf *buf;
	struct i40iw_pfpdu *pfpdu = &qp->pfpdu;
	struct list_head *rxlist = &pfpdu->rxlist;

	if (!pfpdu->mode)
		return;
	while (!list_empty(rxlist)) {
		buf = i40iw_puda_get_listbuf(rxlist);
		i40iw_puda_ret_bufpool(ieq, buf);
	}
}