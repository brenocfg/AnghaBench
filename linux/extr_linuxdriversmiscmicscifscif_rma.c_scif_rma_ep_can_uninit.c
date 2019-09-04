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
struct TYPE_2__ {int /*<<< orphan*/  rma_lock; int /*<<< orphan*/  fence_refcount; int /*<<< orphan*/  tcw_refcount; int /*<<< orphan*/  tw_refcount; int /*<<< orphan*/  mmn_list; int /*<<< orphan*/  remote_reg_list; int /*<<< orphan*/  reg_list; } ;
struct scif_endpt {TYPE_1__ rma_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int scif_rma_ep_can_uninit(struct scif_endpt *ep)
{
	int ret = 0;

	mutex_lock(&ep->rma_info.rma_lock);
	/* Destroy RMA Info only if both lists are empty */
	if (list_empty(&ep->rma_info.reg_list) &&
	    list_empty(&ep->rma_info.remote_reg_list) &&
	    list_empty(&ep->rma_info.mmn_list) &&
	    !atomic_read(&ep->rma_info.tw_refcount) &&
	    !atomic_read(&ep->rma_info.tcw_refcount) &&
	    !atomic_read(&ep->rma_info.fence_refcount))
		ret = 1;
	mutex_unlock(&ep->rma_info.rma_lock);
	return ret;
}