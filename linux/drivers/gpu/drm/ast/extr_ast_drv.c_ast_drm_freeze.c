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
struct drm_device {int /*<<< orphan*/  fb_helper; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_set_suspend_unlocked (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_disable (struct drm_device*) ; 
 int /*<<< orphan*/  pci_save_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ast_drm_freeze(struct drm_device *dev)
{
	drm_kms_helper_poll_disable(dev);
	pci_save_state(dev->pdev);
	drm_fb_helper_set_suspend_unlocked(dev->fb_helper, true);

	return 0;
}