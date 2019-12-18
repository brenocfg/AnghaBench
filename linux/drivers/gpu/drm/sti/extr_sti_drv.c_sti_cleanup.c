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
struct sti_private {int dummy; } ;
struct drm_device {struct sti_private* dev_private; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  component_unbind_all (int /*<<< orphan*/ ,struct drm_device*) ; 
 int /*<<< orphan*/  drm_atomic_helper_shutdown (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  kfree (struct sti_private*) ; 

__attribute__((used)) static void sti_cleanup(struct drm_device *ddev)
{
	struct sti_private *private = ddev->dev_private;

	drm_kms_helper_poll_fini(ddev);
	drm_atomic_helper_shutdown(ddev);
	drm_mode_config_cleanup(ddev);
	component_unbind_all(ddev->dev, ddev);
	kfree(private);
	ddev->dev_private = NULL;
}