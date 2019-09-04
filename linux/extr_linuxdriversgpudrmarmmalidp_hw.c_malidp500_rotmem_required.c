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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct malidp_hw_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ DRM_FORMAT_BGR888 ; 
 scalar_t__ DRM_FORMAT_RGB888 ; 
 int EINVAL ; 
 int drm_format_plane_cpp (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int malidp500_rotmem_required(struct malidp_hw_device *hwdev, u16 w, u16 h, u32 fmt)
{
	/* RGB888 or BGR888 can't be rotated */
	if ((fmt == DRM_FORMAT_RGB888) || (fmt == DRM_FORMAT_BGR888))
		return -EINVAL;

	/*
	 * Each layer needs enough rotation memory to fit 8 lines
	 * worth of pixel data. Required size is then:
	 *    size = rotated_width * (bpp / 8) * 8;
	 */
	return w * drm_format_plane_cpp(fmt, 0) * 8;
}