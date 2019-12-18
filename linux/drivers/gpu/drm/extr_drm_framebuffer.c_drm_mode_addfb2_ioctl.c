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
struct TYPE_2__ {int /*<<< orphan*/  quirk_addfb_prefer_host_byte_order; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int EOPNOTSUPP ; 
 int drm_mode_addfb2 (struct drm_device*,void*,struct drm_file*) ; 

int drm_mode_addfb2_ioctl(struct drm_device *dev,
			  void *data, struct drm_file *file_priv)
{
#ifdef __BIG_ENDIAN
	if (!dev->mode_config.quirk_addfb_prefer_host_byte_order) {
		/*
		 * Drivers must set the
		 * quirk_addfb_prefer_host_byte_order quirk to make
		 * the drm_mode_addfb() compat code work correctly on
		 * bigendian machines.
		 *
		 * If they don't they interpret pixel_format values
		 * incorrectly for bug compatibility, which in turn
		 * implies the ADDFB2 ioctl does not work correctly
		 * then.  So block it to make userspace fallback to
		 * ADDFB.
		 */
		DRM_DEBUG_KMS("addfb2 broken on bigendian");
		return -EOPNOTSUPP;
	}
#endif
	return drm_mode_addfb2(dev, data, file_priv);
}