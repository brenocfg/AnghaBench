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
struct pvrdma_dev {TYPE_2__* netdev; TYPE_1__* pdev; } ;
struct ib_gid_attr {int /*<<< orphan*/  index; int /*<<< orphan*/  device; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pvrdma_del_gid_at_index (struct pvrdma_dev*,int /*<<< orphan*/ ) ; 
 struct pvrdma_dev* to_vdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pvrdma_del_gid(const struct ib_gid_attr *attr, void **context)
{
	struct pvrdma_dev *dev = to_vdev(attr->device);

	dev_dbg(&dev->pdev->dev, "removing gid at index %u from %s",
		attr->index, dev->netdev->name);

	return pvrdma_del_gid_at_index(dev, attr->index);
}