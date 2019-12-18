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
struct uverbs_attr_bundle {int /*<<< orphan*/  driver_udata; TYPE_1__* ufile; } ;
struct inode {int dummy; } ;
struct ib_xrcd {int /*<<< orphan*/  usecnt; struct inode* inode; } ;
struct ib_uverbs_device {int dummy; } ;
struct ib_uobject {int dummy; } ;
typedef  enum rdma_remove_reason { ____Placeholder_rdma_remove_reason } rdma_remove_reason ;
struct TYPE_2__ {struct ib_uverbs_device* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int ib_dealloc_xrcd (struct ib_xrcd*,int /*<<< orphan*/ *) ; 
 scalar_t__ ib_is_destroy_retryable (int,int,struct ib_uobject*) ; 
 int /*<<< orphan*/  xrcd_table_delete (struct ib_uverbs_device*,struct inode*) ; 

int ib_uverbs_dealloc_xrcd(struct ib_uobject *uobject, struct ib_xrcd *xrcd,
			   enum rdma_remove_reason why,
			   struct uverbs_attr_bundle *attrs)
{
	struct inode *inode;
	int ret;
	struct ib_uverbs_device *dev = attrs->ufile->device;

	inode = xrcd->inode;
	if (inode && !atomic_dec_and_test(&xrcd->usecnt))
		return 0;

	ret = ib_dealloc_xrcd(xrcd, &attrs->driver_udata);

	if (ib_is_destroy_retryable(ret, why, uobject)) {
		atomic_inc(&xrcd->usecnt);
		return ret;
	}

	if (inode)
		xrcd_table_delete(dev, inode);

	return ret;
}