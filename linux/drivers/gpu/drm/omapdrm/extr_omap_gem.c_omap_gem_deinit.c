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
struct omap_drm_private {int /*<<< orphan*/  usergart; } ;
struct drm_device {struct omap_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void omap_gem_deinit(struct drm_device *dev)
{
	struct omap_drm_private *priv = dev->dev_private;

	/* I believe we can rely on there being no more outstanding GEM
	 * objects which could depend on usergart/dmm at this point.
	 */
	kfree(priv->usergart);
}