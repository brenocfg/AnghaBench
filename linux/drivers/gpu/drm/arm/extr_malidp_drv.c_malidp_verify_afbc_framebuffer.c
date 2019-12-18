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
struct drm_mode_fb_cmd2 {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ malidp_verify_afbc_framebuffer_caps (struct drm_device*,struct drm_mode_fb_cmd2 const*) ; 
 int malidp_verify_afbc_framebuffer_size (struct drm_device*,struct drm_file*,struct drm_mode_fb_cmd2 const*) ; 

__attribute__((used)) static bool
malidp_verify_afbc_framebuffer(struct drm_device *dev, struct drm_file *file,
			       const struct drm_mode_fb_cmd2 *mode_cmd)
{
	if (malidp_verify_afbc_framebuffer_caps(dev, mode_cmd))
		return malidp_verify_afbc_framebuffer_size(dev, file, mode_cmd);

	return false;
}