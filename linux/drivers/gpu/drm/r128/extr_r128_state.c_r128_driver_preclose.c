#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_file {int dummy; } ;
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_2__ {scalar_t__ page_flipping; } ;
typedef  TYPE_1__ drm_r128_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  r128_do_cleanup_pageflip (struct drm_device*) ; 

void r128_driver_preclose(struct drm_device *dev, struct drm_file *file_priv)
{
	if (dev->dev_private) {
		drm_r128_private_t *dev_priv = dev->dev_private;
		if (dev_priv->page_flipping)
			r128_do_cleanup_pageflip(dev);
	}
}