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
struct usnic_ib_dev {int /*<<< orphan*/  usdev_lock; } ;
struct ib_ucontext {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct usnic_ib_dev* to_usdev (int /*<<< orphan*/ ) ; 
 struct usnic_ib_ucontext* to_uucontext (struct ib_ucontext*) ; 
 int /*<<< orphan*/  usnic_dbg (char*) ; 

void usnic_ib_dealloc_ucontext(struct ib_ucontext *ibcontext)
{
	struct usnic_ib_ucontext *context = to_uucontext(ibcontext);
	struct usnic_ib_dev *us_ibdev = to_usdev(ibcontext->device);
	usnic_dbg("\n");

	mutex_lock(&us_ibdev->usdev_lock);
	WARN_ON_ONCE(!list_empty(&context->qp_grp_list));
	list_del(&context->link);
	mutex_unlock(&us_ibdev->usdev_lock);
}