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
struct TYPE_2__ {scalar_t__ idx; scalar_t__ val; } ;
struct hvutil_transport {int mode; int /*<<< orphan*/  release; TYPE_1__ cn_id; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; int /*<<< orphan*/  outmsg_q; } ;

/* Variables and functions */
 int HVUTIL_TRANSPORT_CHARDEV ; 
 int HVUTIL_TRANSPORT_DESTROY ; 
 int /*<<< orphan*/  cn_del_callback (TYPE_1__*) ; 
 int /*<<< orphan*/  hvt_list_lock ; 
 int /*<<< orphan*/  hvt_transport_free (struct hvutil_transport*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void hvutil_transport_destroy(struct hvutil_transport *hvt)
{
	int mode_old;

	mutex_lock(&hvt->lock);
	mode_old = hvt->mode;
	hvt->mode = HVUTIL_TRANSPORT_DESTROY;
	wake_up_interruptible(&hvt->outmsg_q);
	mutex_unlock(&hvt->lock);

	/*
	 * In case we were in 'chardev' mode we still have an open fd so we
	 * have to defer freeing the device. Netlink interface can be freed
	 * now.
	 */
	spin_lock(&hvt_list_lock);
	list_del(&hvt->list);
	spin_unlock(&hvt_list_lock);
	if (hvt->cn_id.idx > 0 && hvt->cn_id.val > 0)
		cn_del_callback(&hvt->cn_id);

	if (mode_old == HVUTIL_TRANSPORT_CHARDEV)
		wait_for_completion(&hvt->release);

	hvt_transport_free(hvt);
}