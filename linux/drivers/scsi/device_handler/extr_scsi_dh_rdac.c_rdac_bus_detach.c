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
struct scsi_device {struct rdac_dh_data* handler_data; } ;
struct rdac_dh_data {TYPE_1__* ctlr; int /*<<< orphan*/ * sdev; int /*<<< orphan*/  node; } ;
struct TYPE_2__ {int /*<<< orphan*/  kref; scalar_t__ ms_queued; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rdac_dh_data*) ; 
 int /*<<< orphan*/  kmpath_rdacd ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  release_controller ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rdac_bus_detach( struct scsi_device *sdev )
{
	struct rdac_dh_data *h = sdev->handler_data;

	if (h->ctlr && h->ctlr->ms_queued)
		flush_workqueue(kmpath_rdacd);

	spin_lock(&list_lock);
	if (h->ctlr) {
		list_del_rcu(&h->node);
		h->sdev = NULL;
		kref_put(&h->ctlr->kref, release_controller);
	}
	spin_unlock(&list_lock);
	sdev->handler_data = NULL;
	kfree(h);
}