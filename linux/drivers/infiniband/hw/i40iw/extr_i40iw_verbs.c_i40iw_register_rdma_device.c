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
struct i40iw_ib_device {int /*<<< orphan*/  ibdev; } ;
struct i40iw_device {struct i40iw_ib_device* iwibdev; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  i40iw_attr_group ; 
 struct i40iw_ib_device* i40iw_init_rdma_device (struct i40iw_device*) ; 
 int /*<<< orphan*/  ib_dealloc_device (int /*<<< orphan*/ *) ; 
 int ib_device_set_netdev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ib_register_device (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  rdma_set_device_sysfs_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int i40iw_register_rdma_device(struct i40iw_device *iwdev)
{
	int ret;
	struct i40iw_ib_device *iwibdev;

	iwdev->iwibdev = i40iw_init_rdma_device(iwdev);
	if (!iwdev->iwibdev)
		return -ENOMEM;
	iwibdev = iwdev->iwibdev;
	rdma_set_device_sysfs_group(&iwibdev->ibdev, &i40iw_attr_group);
	ret = ib_device_set_netdev(&iwibdev->ibdev, iwdev->netdev, 1);
	if (ret)
		goto error;

	ret = ib_register_device(&iwibdev->ibdev, "i40iw%d");
	if (ret)
		goto error;

	return 0;
error:
	ib_dealloc_device(&iwdev->iwibdev->ibdev);
	return ret;
}