#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_mode_fb_cmd2 {int /*<<< orphan*/  pixel_format; } ;
struct drm_format_info {int dummy; } ;
struct TYPE_4__ {TYPE_1__* funcs; } ;
struct drm_device {TYPE_2__ mode_config; } ;
struct TYPE_3__ {struct drm_format_info* (* get_format_info ) (struct drm_mode_fb_cmd2 const*) ;} ;

/* Variables and functions */
 struct drm_format_info* drm_format_info (int /*<<< orphan*/ ) ; 
 struct drm_format_info* stub1 (struct drm_mode_fb_cmd2 const*) ; 

const struct drm_format_info *
drm_get_format_info(struct drm_device *dev,
		    const struct drm_mode_fb_cmd2 *mode_cmd)
{
	const struct drm_format_info *info = NULL;

	if (dev->mode_config.funcs->get_format_info)
		info = dev->mode_config.funcs->get_format_info(mode_cmd);

	if (!info)
		info = drm_format_info(mode_cmd->pixel_format);

	return info;
}