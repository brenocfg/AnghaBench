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
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sys_image_guid; int /*<<< orphan*/  device_cap_flags; } ;
struct ib_device {int /*<<< orphan*/  node_type; TYPE_1__ attrs; int /*<<< orphan*/  node_guid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EMSGSIZE ; 
 int IB_FW_VERSION_NAME_MAX ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_CAP_FLAGS ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_DEV_NODE_TYPE ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_FW_VERSION ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_NODE_GUID ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_PAD ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_PORT_INDEX ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_SYS_IMAGE_GUID ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ fill_nldev_handle (struct sk_buff*,struct ib_device*) ; 
 int /*<<< orphan*/  ib_get_device_fw_str (struct ib_device*,char*) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_end_port (struct ib_device*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int fill_dev_info(struct sk_buff *msg, struct ib_device *device)
{
	char fw[IB_FW_VERSION_NAME_MAX];

	if (fill_nldev_handle(msg, device))
		return -EMSGSIZE;

	if (nla_put_u32(msg, RDMA_NLDEV_ATTR_PORT_INDEX, rdma_end_port(device)))
		return -EMSGSIZE;

	BUILD_BUG_ON(sizeof(device->attrs.device_cap_flags) != sizeof(u64));
	if (nla_put_u64_64bit(msg, RDMA_NLDEV_ATTR_CAP_FLAGS,
			      device->attrs.device_cap_flags,
			      RDMA_NLDEV_ATTR_PAD))
		return -EMSGSIZE;

	ib_get_device_fw_str(device, fw);
	/* Device without FW has strlen(fw) = 0 */
	if (strlen(fw) && nla_put_string(msg, RDMA_NLDEV_ATTR_FW_VERSION, fw))
		return -EMSGSIZE;

	if (nla_put_u64_64bit(msg, RDMA_NLDEV_ATTR_NODE_GUID,
			      be64_to_cpu(device->node_guid),
			      RDMA_NLDEV_ATTR_PAD))
		return -EMSGSIZE;
	if (nla_put_u64_64bit(msg, RDMA_NLDEV_ATTR_SYS_IMAGE_GUID,
			      be64_to_cpu(device->attrs.sys_image_guid),
			      RDMA_NLDEV_ATTR_PAD))
		return -EMSGSIZE;
	if (nla_put_u8(msg, RDMA_NLDEV_ATTR_DEV_NODE_TYPE, device->node_type))
		return -EMSGSIZE;
	return 0;
}