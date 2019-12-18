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
struct qxl_device {int /*<<< orphan*/  release_ring; int /*<<< orphan*/  command_ring; } ;
struct pci_dev {int dummy; } ;
struct drm_device {struct qxl_device* dev_private; struct pci_dev* pdev; } ;

/* Variables and functions */
 int drm_mode_config_helper_suspend (struct drm_device*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  qxl_check_idle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qxl_destroy_monitors_object (struct qxl_device*) ; 
 int /*<<< orphan*/  qxl_queue_garbage_collect (struct qxl_device*,int) ; 
 int /*<<< orphan*/  qxl_surf_evict (struct qxl_device*) ; 
 int /*<<< orphan*/  qxl_vram_evict (struct qxl_device*) ; 

__attribute__((used)) static int qxl_drm_freeze(struct drm_device *dev)
{
	struct pci_dev *pdev = dev->pdev;
	struct qxl_device *qdev = dev->dev_private;
	int ret;

	ret = drm_mode_config_helper_suspend(dev);
	if (ret)
		return ret;

	qxl_destroy_monitors_object(qdev);
	qxl_surf_evict(qdev);
	qxl_vram_evict(qdev);

	while (!qxl_check_idle(qdev->command_ring));
	while (!qxl_check_idle(qdev->release_ring))
		qxl_queue_garbage_collect(qdev, 1);

	pci_save_state(pdev);

	return 0;
}