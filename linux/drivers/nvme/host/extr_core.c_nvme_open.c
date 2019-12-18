#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nvme_ns {TYPE_4__* ctrl; int /*<<< orphan*/  kref; TYPE_2__* head; } ;
struct block_device {TYPE_1__* bd_disk; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_8__ {TYPE_3__* ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  module; } ;
struct TYPE_6__ {int /*<<< orphan*/  disk; } ;
struct TYPE_5__ {struct nvme_ns* private_data; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_put_ns (struct nvme_ns*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvme_open(struct block_device *bdev, fmode_t mode)
{
	struct nvme_ns *ns = bdev->bd_disk->private_data;

#ifdef CONFIG_NVME_MULTIPATH
	/* should never be called due to GENHD_FL_HIDDEN */
	if (WARN_ON_ONCE(ns->head->disk))
		goto fail;
#endif
	if (!kref_get_unless_zero(&ns->kref))
		goto fail;
	if (!try_module_get(ns->ctrl->ops->module))
		goto fail_put_ns;

	return 0;

fail_put_ns:
	nvme_put_ns(ns);
fail:
	return -ENXIO;
}