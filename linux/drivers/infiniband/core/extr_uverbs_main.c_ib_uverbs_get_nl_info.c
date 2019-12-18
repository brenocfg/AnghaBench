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
struct ib_uverbs_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver_id; int /*<<< orphan*/  uverbs_no_driver_id_binding; int /*<<< orphan*/  uverbs_abi_ver; } ;
struct ib_device {TYPE_1__ ops; } ;
struct ib_client_nl_info {int port; int /*<<< orphan*/  nl_msg; int /*<<< orphan*/ * cdev; int /*<<< orphan*/  abi; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_UVERBS_DRIVER_ID ; 
 int nla_put_u32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ib_uverbs_get_nl_info(struct ib_device *ibdev, void *client_data,
				 struct ib_client_nl_info *res)
{
	struct ib_uverbs_device *uverbs_dev = client_data;
	int ret;

	if (res->port != -1)
		return -EINVAL;

	res->abi = ibdev->ops.uverbs_abi_ver;
	res->cdev = &uverbs_dev->dev;

	/*
	 * To support DRIVER_ID binding in userspace some of the driver need
	 * upgrading to expose their PCI dependent revision information
	 * through get_context instead of relying on modalias matching. When
	 * the drivers are fixed they can drop this flag.
	 */
	if (!ibdev->ops.uverbs_no_driver_id_binding) {
		ret = nla_put_u32(res->nl_msg, RDMA_NLDEV_ATTR_UVERBS_DRIVER_ID,
				  ibdev->ops.driver_id);
		if (ret)
			return ret;
	}
	return 0;
}