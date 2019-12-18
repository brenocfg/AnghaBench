#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* device; } ;
struct nvme_dev {scalar_t__ cmb_size; TYPE_2__ ctrl; } ;
struct TYPE_6__ {int /*<<< orphan*/  attr; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 TYPE_3__ dev_attr_cmb ; 
 int /*<<< orphan*/  sysfs_remove_file_from_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void nvme_release_cmb(struct nvme_dev *dev)
{
	if (dev->cmb_size) {
		sysfs_remove_file_from_group(&dev->ctrl.device->kobj,
					     &dev_attr_cmb.attr, NULL);
		dev->cmb_size = 0;
	}
}