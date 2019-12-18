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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct drm_framebuffer {int /*<<< orphan*/  modifier; TYPE_2__* format; TYPE_1__* dev; } ;
struct komeda_fb {struct drm_framebuffer base; } ;
struct komeda_dev {int /*<<< orphan*/  fmt_tbl; } ;
struct TYPE_4__ {int /*<<< orphan*/  format; } ;
struct TYPE_3__ {struct komeda_dev* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int komeda_format_mod_supported (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  komeda_get_format_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool komeda_fb_is_layer_supported(struct komeda_fb *kfb, u32 layer_type,
				  u32 rot)
{
	struct drm_framebuffer *fb = &kfb->base;
	struct komeda_dev *mdev = fb->dev->dev_private;
	u32 fourcc = fb->format->format;
	u64 modifier = fb->modifier;
	bool supported;

	supported = komeda_format_mod_supported(&mdev->fmt_tbl, layer_type,
						fourcc, modifier, rot);
	if (!supported)
		DRM_DEBUG_ATOMIC("Layer TYPE: %d doesn't support fb FMT: %s.\n",
			layer_type, komeda_get_format_name(fourcc, modifier));

	return supported;
}