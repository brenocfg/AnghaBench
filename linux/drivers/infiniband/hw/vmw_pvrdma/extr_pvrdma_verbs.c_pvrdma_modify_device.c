#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ib_device_modify {int /*<<< orphan*/  sys_image_guid; int /*<<< orphan*/  node_desc; } ;
struct ib_device {int /*<<< orphan*/  node_desc; } ;
struct TYPE_4__ {int /*<<< orphan*/  port_mutex; int /*<<< orphan*/  sys_image_guid; int /*<<< orphan*/  desc_lock; TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int IB_DEVICE_MODIFY_NODE_DESC ; 
 int IB_DEVICE_MODIFY_SYS_IMAGE_GUID ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_2__* to_vdev (struct ib_device*) ; 

int pvrdma_modify_device(struct ib_device *ibdev, int mask,
			 struct ib_device_modify *props)
{
	unsigned long flags;

	if (mask & ~(IB_DEVICE_MODIFY_SYS_IMAGE_GUID |
		     IB_DEVICE_MODIFY_NODE_DESC)) {
		dev_warn(&to_vdev(ibdev)->pdev->dev,
			 "unsupported device modify mask %#x\n", mask);
		return -EOPNOTSUPP;
	}

	if (mask & IB_DEVICE_MODIFY_NODE_DESC) {
		spin_lock_irqsave(&to_vdev(ibdev)->desc_lock, flags);
		memcpy(ibdev->node_desc, props->node_desc, 64);
		spin_unlock_irqrestore(&to_vdev(ibdev)->desc_lock, flags);
	}

	if (mask & IB_DEVICE_MODIFY_SYS_IMAGE_GUID) {
		mutex_lock(&to_vdev(ibdev)->port_mutex);
		to_vdev(ibdev)->sys_image_guid =
			cpu_to_be64(props->sys_image_guid);
		mutex_unlock(&to_vdev(ibdev)->port_mutex);
	}

	return 0;
}