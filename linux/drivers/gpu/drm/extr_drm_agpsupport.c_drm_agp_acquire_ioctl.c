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
struct drm_file {TYPE_1__* minor; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ dev; } ;

/* Variables and functions */
 int drm_agp_acquire (struct drm_device*) ; 

int drm_agp_acquire_ioctl(struct drm_device *dev, void *data,
			  struct drm_file *file_priv)
{
	return drm_agp_acquire((struct drm_device *) file_priv->minor->dev);
}