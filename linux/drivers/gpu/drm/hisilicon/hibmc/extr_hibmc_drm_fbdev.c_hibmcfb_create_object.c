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
typedef  int u32 ;
struct hibmc_drm_private {struct drm_device* dev; } ;
struct drm_mode_fb_cmd2 {int* pitches; int height; } ;
struct drm_gem_object {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int hibmc_gem_create (struct drm_device*,int,int,struct drm_gem_object**) ; 

__attribute__((used)) static int hibmcfb_create_object(
				struct hibmc_drm_private *priv,
				const struct drm_mode_fb_cmd2 *mode_cmd,
				struct drm_gem_object **gobj_p)
{
	struct drm_gem_object *gobj;
	struct drm_device *dev = priv->dev;
	u32 size;
	int ret = 0;

	size = mode_cmd->pitches[0] * mode_cmd->height;
	ret = hibmc_gem_create(dev, size, true, &gobj);
	if (ret)
		return ret;

	*gobj_p = gobj;
	return ret;
}