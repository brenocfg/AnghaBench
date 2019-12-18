#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int u32 ;
struct TYPE_6__ {int backup_size; } ;
struct drm_vmw_size {scalar_t__ width; scalar_t__ height; } ;
struct vmw_surface {int flags; int scanout; int num_sizes; int multisample_count; TYPE_3__ res; scalar_t__* mip_levels; struct drm_vmw_size base_size; int /*<<< orphan*/  format; int /*<<< orphan*/  quality_level; int /*<<< orphan*/  multisample_pattern; scalar_t__ array_size; int /*<<< orphan*/  autogen_filter; int /*<<< orphan*/ * offsets; int /*<<< orphan*/ * sizes; } ;
struct TYPE_4__ {int shareable; int /*<<< orphan*/ * tfile; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct vmw_user_surface {struct vmw_surface srf; TYPE_2__ prime; scalar_t__ size; } ;
struct vmw_private {scalar_t__ texture_max_width; scalar_t__ texture_max_height; scalar_t__ active_display_unit; scalar_t__ stdu_max_width; scalar_t__ stdu_max_height; int /*<<< orphan*/  reservation_sem; int /*<<< orphan*/  has_dx; } ;
struct ttm_operation_ctx {int interruptible; int no_wait_gpu; } ;
struct svga3d_surface_desc {scalar_t__ block_desc; } ;
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  SVGA3dSurfaceFormat ;
typedef  int SVGA3dSurfaceAllFlags ;
typedef  int /*<<< orphan*/  SVGA3dMSQualityLevel ;
typedef  int /*<<< orphan*/  SVGA3dMSPattern ;
typedef  int /*<<< orphan*/  SVGA3dDXSOState ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ SVGA3DBLOCKDESC_NONE ; 
 int SVGA3D_MAX_SURFACE_FACES ; 
 int SVGA3D_SURFACE_BIND_STREAM_OUTPUT ; 
 int SVGA3D_SURFACE_CUBEMAP ; 
 int SVGA3D_SURFACE_MULTISAMPLE ; 
 int SVGA3D_SURFACE_SCREENTARGET ; 
 int /*<<< orphan*/  SVGA3D_TEX_FILTER_NONE ; 
 int /*<<< orphan*/  VMW_DEBUG_USER (char*,...) ; 
 struct vmw_user_surface* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct svga3d_surface_desc* svga3dsurface_get_desc (int /*<<< orphan*/ ) ; 
 int svga3dsurface_get_serialized_size_extended (int /*<<< orphan*/ ,struct drm_vmw_size,scalar_t__,int,int) ; 
 int /*<<< orphan*/  svga3dsurface_is_screen_target_format (int /*<<< orphan*/ ) ; 
 int ttm_mem_global_alloc (int /*<<< orphan*/ ,scalar_t__,struct ttm_operation_ctx*) ; 
 int /*<<< orphan*/  ttm_mem_global_free (int /*<<< orphan*/ ,scalar_t__) ; 
 int ttm_read_lock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ttm_read_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vmw_du_screen_target ; 
 int /*<<< orphan*/  vmw_mem_glob (struct vmw_private*) ; 
 struct vmw_private* vmw_priv (struct drm_device*) ; 
 int vmw_surface_init (struct vmw_private*,struct vmw_surface*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_user_surface_free ; 

int vmw_surface_gb_priv_define(struct drm_device *dev,
			       uint32_t user_accounting_size,
			       SVGA3dSurfaceAllFlags svga3d_flags,
			       SVGA3dSurfaceFormat format,
			       bool for_scanout,
			       uint32_t num_mip_levels,
			       uint32_t multisample_count,
			       uint32_t array_size,
			       struct drm_vmw_size size,
			       SVGA3dMSPattern multisample_pattern,
			       SVGA3dMSQualityLevel quality_level,
			       struct vmw_surface **srf_out)
{
	struct vmw_private *dev_priv = vmw_priv(dev);
	struct vmw_user_surface *user_srf;
	struct ttm_operation_ctx ctx = {
		.interruptible = true,
		.no_wait_gpu = false
	};
	struct vmw_surface *srf;
	int ret;
	u32 num_layers = 1;
	u32 sample_count = 1;

	*srf_out = NULL;

	if (for_scanout) {
		if (!svga3dsurface_is_screen_target_format(format)) {
			VMW_DEBUG_USER("Invalid Screen Target surface format.");
			return -EINVAL;
		}

		if (size.width > dev_priv->texture_max_width ||
		    size.height > dev_priv->texture_max_height) {
			VMW_DEBUG_USER("%ux%u\n, exceeds max surface size %ux%u",
				       size.width, size.height,
				       dev_priv->texture_max_width,
				       dev_priv->texture_max_height);
			return -EINVAL;
		}
	} else {
		const struct svga3d_surface_desc *desc;

		desc = svga3dsurface_get_desc(format);
		if (unlikely(desc->block_desc == SVGA3DBLOCKDESC_NONE)) {
			VMW_DEBUG_USER("Invalid surface format.\n");
			return -EINVAL;
		}
	}

	/* array_size must be null for non-GL3 host. */
	if (array_size > 0 && !dev_priv->has_dx) {
		VMW_DEBUG_USER("Tried to create DX surface on non-DX host.\n");
		return -EINVAL;
	}

	ret = ttm_read_lock(&dev_priv->reservation_sem, true);
	if (unlikely(ret != 0))
		return ret;

	ret = ttm_mem_global_alloc(vmw_mem_glob(dev_priv),
				   user_accounting_size, &ctx);
	if (unlikely(ret != 0)) {
		if (ret != -ERESTARTSYS)
			DRM_ERROR("Out of graphics memory for surface"
				  " creation.\n");
		goto out_unlock;
	}

	user_srf = kzalloc(sizeof(*user_srf), GFP_KERNEL);
	if (unlikely(!user_srf)) {
		ret = -ENOMEM;
		goto out_no_user_srf;
	}

	*srf_out  = &user_srf->srf;
	user_srf->size = user_accounting_size;
	user_srf->prime.base.shareable = false;
	user_srf->prime.base.tfile     = NULL;

	srf = &user_srf->srf;
	srf->flags             = svga3d_flags;
	srf->format            = format;
	srf->scanout           = for_scanout;
	srf->mip_levels[0]     = num_mip_levels;
	srf->num_sizes         = 1;
	srf->sizes             = NULL;
	srf->offsets           = NULL;
	srf->base_size         = size;
	srf->autogen_filter    = SVGA3D_TEX_FILTER_NONE;
	srf->array_size        = array_size;
	srf->multisample_count = multisample_count;
	srf->multisample_pattern = multisample_pattern;
	srf->quality_level = quality_level;

	if (array_size)
		num_layers = array_size;
	else if (svga3d_flags & SVGA3D_SURFACE_CUBEMAP)
		num_layers = SVGA3D_MAX_SURFACE_FACES;

	if (srf->flags & SVGA3D_SURFACE_MULTISAMPLE)
		sample_count = srf->multisample_count;

	srf->res.backup_size   =
		svga3dsurface_get_serialized_size_extended(srf->format,
							   srf->base_size,
							   srf->mip_levels[0],
							   num_layers,
							   sample_count);

	if (srf->flags & SVGA3D_SURFACE_BIND_STREAM_OUTPUT)
		srf->res.backup_size += sizeof(SVGA3dDXSOState);

	/*
	 * Don't set SVGA3D_SURFACE_SCREENTARGET flag for a scanout surface with
	 * size greater than STDU max width/height. This is really a workaround
	 * to support creation of big framebuffer requested by some user-space
	 * for whole topology. That big framebuffer won't really be used for
	 * binding with screen target as during prepare_fb a separate surface is
	 * created so it's safe to ignore SVGA3D_SURFACE_SCREENTARGET flag.
	 */
	if (dev_priv->active_display_unit == vmw_du_screen_target &&
	    for_scanout && size.width <= dev_priv->stdu_max_width &&
	    size.height <= dev_priv->stdu_max_height)
		srf->flags |= SVGA3D_SURFACE_SCREENTARGET;

	/*
	 * From this point, the generic resource management functions
	 * destroy the object on failure.
	 */
	ret = vmw_surface_init(dev_priv, srf, vmw_user_surface_free);

	ttm_read_unlock(&dev_priv->reservation_sem);
	return ret;

out_no_user_srf:
	ttm_mem_global_free(vmw_mem_glob(dev_priv), user_accounting_size);

out_unlock:
	ttm_read_unlock(&dev_priv->reservation_sem);
	return ret;
}