#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vmw_private {int active_display_unit; int capabilities; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct vmw_framebuffer {scalar_t__ bo; TYPE_4__ base; } ;
struct vmw_buffer_object {int dummy; } ;
struct ttm_placement {int dummy; } ;
struct TYPE_11__ {struct vmw_buffer_object* buffer; } ;
struct TYPE_9__ {TYPE_2__* surface; } ;
struct TYPE_7__ {struct vmw_buffer_object* backup; } ;
struct TYPE_8__ {TYPE_1__ res; } ;

/* Variables and functions */
 int EINVAL ; 
 int SVGA_CAP_3D ; 
 int vmw_bo_pin_in_placement (struct vmw_private*,struct vmw_buffer_object*,struct ttm_placement*,int) ; 
 int vmw_bo_pin_in_start_of_vram (struct vmw_private*,struct vmw_buffer_object*,int) ; 
#define  vmw_du_legacy 130 
#define  vmw_du_screen_object 129 
#define  vmw_du_screen_target 128 
 TYPE_5__* vmw_framebuffer_to_vfbd (TYPE_4__*) ; 
 TYPE_3__* vmw_framebuffer_to_vfbs (TYPE_4__*) ; 
 struct ttm_placement vmw_mob_placement ; 
 int /*<<< orphan*/  vmw_overlay_pause_all (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_overlay_resume_all (struct vmw_private*) ; 
 struct vmw_private* vmw_priv (int /*<<< orphan*/ ) ; 
 struct ttm_placement vmw_sys_placement ; 
 struct ttm_placement vmw_vram_gmr_placement ; 

__attribute__((used)) static int vmw_framebuffer_pin(struct vmw_framebuffer *vfb)
{
	struct vmw_private *dev_priv = vmw_priv(vfb->base.dev);
	struct vmw_buffer_object *buf;
	struct ttm_placement *placement;
	int ret;

	buf = vfb->bo ?  vmw_framebuffer_to_vfbd(&vfb->base)->buffer :
		vmw_framebuffer_to_vfbs(&vfb->base)->surface->res.backup;

	if (!buf)
		return 0;

	switch (dev_priv->active_display_unit) {
	case vmw_du_legacy:
		vmw_overlay_pause_all(dev_priv);
		ret = vmw_bo_pin_in_start_of_vram(dev_priv, buf, false);
		vmw_overlay_resume_all(dev_priv);
		break;
	case vmw_du_screen_object:
	case vmw_du_screen_target:
		if (vfb->bo) {
			if (dev_priv->capabilities & SVGA_CAP_3D) {
				/*
				 * Use surface DMA to get content to
				 * sreen target surface.
				 */
				placement = &vmw_vram_gmr_placement;
			} else {
				/* Use CPU blit. */
				placement = &vmw_sys_placement;
			}
		} else {
			/* Use surface / image update */
			placement = &vmw_mob_placement;
		}

		return vmw_bo_pin_in_placement(dev_priv, buf, placement, false);
	default:
		return -EINVAL;
	}

	return ret;
}