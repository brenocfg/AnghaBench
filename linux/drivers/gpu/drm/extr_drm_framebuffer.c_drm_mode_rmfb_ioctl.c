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
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int drm_mode_rmfb (struct drm_device*,int /*<<< orphan*/ ,struct drm_file*) ; 

int drm_mode_rmfb_ioctl(struct drm_device *dev,
			void *data, struct drm_file *file_priv)
{
	uint32_t *fb_id = data;

	return drm_mode_rmfb(dev, *fb_id, file_priv);
}