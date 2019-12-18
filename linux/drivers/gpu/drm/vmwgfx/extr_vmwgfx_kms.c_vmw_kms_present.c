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
struct vmw_surface {int /*<<< orphan*/  res; } ;
struct vmw_private {int active_display_unit; } ;
struct vmw_framebuffer {int dummy; } ;
struct drm_vmw_rect {int dummy; } ;
struct drm_file {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
#define  vmw_du_screen_object 129 
#define  vmw_du_screen_target 128 
 int /*<<< orphan*/  vmw_fifo_flush (struct vmw_private*,int) ; 
 int vmw_kms_generic_present (struct vmw_private*,struct drm_file*,struct vmw_framebuffer*,struct vmw_surface*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_vmw_rect*,int /*<<< orphan*/ ) ; 
 int vmw_kms_stdu_surface_dirty (struct vmw_private*,struct vmw_framebuffer*,int /*<<< orphan*/ *,struct drm_vmw_rect*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int vmw_kms_present(struct vmw_private *dev_priv,
		    struct drm_file *file_priv,
		    struct vmw_framebuffer *vfb,
		    struct vmw_surface *surface,
		    uint32_t sid,
		    int32_t destX, int32_t destY,
		    struct drm_vmw_rect *clips,
		    uint32_t num_clips)
{
	int ret;

	switch (dev_priv->active_display_unit) {
	case vmw_du_screen_target:
		ret = vmw_kms_stdu_surface_dirty(dev_priv, vfb, NULL, clips,
						 &surface->res, destX, destY,
						 num_clips, 1, NULL, NULL);
		break;
	case vmw_du_screen_object:
		ret = vmw_kms_generic_present(dev_priv, file_priv, vfb, surface,
					      sid, destX, destY, clips,
					      num_clips);
		break;
	default:
		WARN_ONCE(true,
			  "Present called with invalid display system.\n");
		ret = -ENOSYS;
		break;
	}
	if (ret)
		return ret;

	vmw_fifo_flush(dev_priv, false);

	return 0;
}