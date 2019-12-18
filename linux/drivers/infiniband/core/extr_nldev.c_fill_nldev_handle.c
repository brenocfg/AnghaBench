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
struct sk_buff {int dummy; } ;
struct ib_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_DEV_INDEX ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_DEV_NAME ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fill_nldev_handle(struct sk_buff *msg, struct ib_device *device)
{
	if (nla_put_u32(msg, RDMA_NLDEV_ATTR_DEV_INDEX, device->index))
		return -EMSGSIZE;
	if (nla_put_string(msg, RDMA_NLDEV_ATTR_DEV_NAME,
			   dev_name(&device->dev)))
		return -EMSGSIZE;

	return 0;
}