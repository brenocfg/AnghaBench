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
struct hibmc_drm_private {int /*<<< orphan*/ * fbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hibmc_fbdev_destroy (int /*<<< orphan*/ *) ; 

void hibmc_fbdev_fini(struct hibmc_drm_private *priv)
{
	if (!priv->fbdev)
		return;

	hibmc_fbdev_destroy(priv->fbdev);
	priv->fbdev = NULL;
}