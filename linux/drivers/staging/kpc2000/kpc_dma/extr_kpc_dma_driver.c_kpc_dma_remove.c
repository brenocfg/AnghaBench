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
struct platform_device {int dummy; } ;
struct kpc_dma_device {TYPE_2__* pldev; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; TYPE_1__ dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assigned_major_num ; 
 int /*<<< orphan*/  destroy_dma_engine (struct kpc_dma_device*) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct kpc_dma_device*) ; 
 int /*<<< orphan*/  kpc_dma_class ; 
 int /*<<< orphan*/  kpc_dma_del_device (struct kpc_dma_device*) ; 
 int /*<<< orphan*/  lock_engine (struct kpc_dma_device*) ; 
 int /*<<< orphan*/  ndd_attr_list ; 
 struct kpc_dma_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sysfs_remove_files (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int  kpc_dma_remove(struct platform_device *pldev)
{
	struct kpc_dma_device *ldev = platform_get_drvdata(pldev);

	if (!ldev)
		return -ENXIO;

	lock_engine(ldev);
	sysfs_remove_files(&(ldev->pldev->dev.kobj), ndd_attr_list);
	destroy_dma_engine(ldev);
	kpc_dma_del_device(ldev);
	device_destroy(kpc_dma_class, MKDEV(assigned_major_num, ldev->pldev->id));
	kfree(ldev);

	return 0;
}