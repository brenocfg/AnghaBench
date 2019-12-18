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
struct intel_fbdev {int dummy; } ;
struct drm_i915_private {int /*<<< orphan*/  fbdev; } ;

/* Variables and functions */
 struct intel_fbdev* fetch_and_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_fbdev_destroy (struct intel_fbdev*) ; 

void intel_fbdev_fini(struct drm_i915_private *dev_priv)
{
	struct intel_fbdev *ifbdev = fetch_and_zero(&dev_priv->fbdev);

	if (!ifbdev)
		return;

	intel_fbdev_destroy(ifbdev);
}