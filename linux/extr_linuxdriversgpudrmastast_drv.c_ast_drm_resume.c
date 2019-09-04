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
struct drm_device {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int EIO ; 
 int ast_drm_thaw (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_enable (struct drm_device*) ; 
 scalar_t__ pci_enable_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ast_drm_resume(struct drm_device *dev)
{
	int ret;

	if (pci_enable_device(dev->pdev))
		return -EIO;

	ret = ast_drm_thaw(dev);
	if (ret)
		return ret;

	drm_kms_helper_poll_enable(dev);
	return 0;
}