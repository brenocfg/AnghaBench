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
struct usnic_ib_ucontext {int /*<<< orphan*/  link; int /*<<< orphan*/  qp_grp_list; } ;
struct usnic_ib_dev {int /*<<< orphan*/  usdev_lock; int /*<<< orphan*/  ctx_list; } ;
struct ib_udata {int dummy; } ;
struct ib_ucontext {struct ib_device* device; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct usnic_ib_ucontext* to_ucontext (struct ib_ucontext*) ; 
 struct usnic_ib_dev* to_usdev (struct ib_device*) ; 
 int /*<<< orphan*/  usnic_dbg (char*) ; 

int usnic_ib_alloc_ucontext(struct ib_ucontext *uctx, struct ib_udata *udata)
{
	struct ib_device *ibdev = uctx->device;
	struct usnic_ib_ucontext *context = to_ucontext(uctx);
	struct usnic_ib_dev *us_ibdev = to_usdev(ibdev);
	usnic_dbg("\n");

	INIT_LIST_HEAD(&context->qp_grp_list);
	mutex_lock(&us_ibdev->usdev_lock);
	list_add_tail(&context->link, &us_ibdev->ctx_list);
	mutex_unlock(&us_ibdev->usdev_lock);

	return 0;
}