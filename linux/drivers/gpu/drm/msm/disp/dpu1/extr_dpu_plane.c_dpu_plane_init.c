#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ u32 ;
struct msm_drm_private {int /*<<< orphan*/  kms; } ;
struct TYPE_15__ {int id; } ;
struct drm_plane {TYPE_5__ base; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;
struct dpu_plane {int pipe; int is_virtual; TYPE_6__* pipe_hw; int /*<<< orphan*/  pipe_name; int /*<<< orphan*/  lock; TYPE_7__* catalog; TYPE_2__* pipe_sblk; int /*<<< orphan*/  features; int /*<<< orphan*/  mplane_list; struct drm_plane base; } ;
struct dpu_kms {TYPE_7__* catalog; int /*<<< orphan*/  mmio; } ;
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;
struct TYPE_17__ {TYPE_4__* mixer; scalar_t__ mixer_count; } ;
struct TYPE_16__ {TYPE_1__* cap; } ;
struct TYPE_14__ {TYPE_3__* sblk; } ;
struct TYPE_13__ {int maxblendstages; } ;
struct TYPE_12__ {int* virt_format_list; int virt_num_formats; int* format_list; int num_formats; } ;
struct TYPE_11__ {TYPE_2__* sblk; int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG (char*,int /*<<< orphan*/ ,int,int,scalar_t__) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,int) ; 
 int /*<<< orphan*/  DPU_NAME_SIZE ; 
 int DPU_STAGE_0 ; 
 int DPU_STAGE_MAX ; 
 int DPU_ZPOS_MAX ; 
 int DRM_MODE_REFLECT_X ; 
 int DRM_MODE_REFLECT_Y ; 
 int DRM_MODE_ROTATE_0 ; 
 int DRM_MODE_ROTATE_180 ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct drm_plane* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (TYPE_6__*) ; 
 int PTR_ERR (TYPE_6__*) ; 
 int /*<<< orphan*/  dpu_hw_sspp_destroy (TYPE_6__*) ; 
 TYPE_6__* dpu_hw_sspp_init (int,int /*<<< orphan*/ ,TYPE_7__*,int) ; 
 int /*<<< orphan*/  dpu_plane_funcs ; 
 int /*<<< orphan*/  dpu_plane_helper_funcs ; 
 int /*<<< orphan*/  drm_plane_create_rotation_property (struct drm_plane*,int,int) ; 
 int drm_plane_create_zpos_property (struct drm_plane*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_plane_enable_fb_damage_clips (struct drm_plane*) ; 
 struct drm_plane* drm_plane_find (struct drm_device*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  drm_plane_helper_add (struct drm_plane*,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (struct drm_device*,struct drm_plane*,int,int /*<<< orphan*/ *,int const*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dpu_plane*) ; 
 struct dpu_plane* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  supported_format_modifiers ; 
 struct dpu_kms* to_dpu_kms (int /*<<< orphan*/ ) ; 
 struct dpu_plane* to_dpu_plane (struct drm_plane*) ; 

struct drm_plane *dpu_plane_init(struct drm_device *dev,
		uint32_t pipe, enum drm_plane_type type,
		unsigned long possible_crtcs, u32 master_plane_id)
{
	struct drm_plane *plane = NULL, *master_plane = NULL;
	const uint32_t *format_list;
	struct dpu_plane *pdpu;
	struct msm_drm_private *priv = dev->dev_private;
	struct dpu_kms *kms = to_dpu_kms(priv->kms);
	int zpos_max = DPU_ZPOS_MAX;
	uint32_t num_formats;
	int ret = -EINVAL;

	/* create and zero local structure */
	pdpu = kzalloc(sizeof(*pdpu), GFP_KERNEL);
	if (!pdpu) {
		DPU_ERROR("[%u]failed to allocate local plane struct\n", pipe);
		ret = -ENOMEM;
		return ERR_PTR(ret);
	}

	/* cache local stuff for later */
	plane = &pdpu->base;
	pdpu->pipe = pipe;
	pdpu->is_virtual = (master_plane_id != 0);
	INIT_LIST_HEAD(&pdpu->mplane_list);
	master_plane = drm_plane_find(dev, NULL, master_plane_id);
	if (master_plane) {
		struct dpu_plane *mpdpu = to_dpu_plane(master_plane);

		list_add_tail(&pdpu->mplane_list, &mpdpu->mplane_list);
	}

	/* initialize underlying h/w driver */
	pdpu->pipe_hw = dpu_hw_sspp_init(pipe, kms->mmio, kms->catalog,
							master_plane_id != 0);
	if (IS_ERR(pdpu->pipe_hw)) {
		DPU_ERROR("[%u]SSPP init failed\n", pipe);
		ret = PTR_ERR(pdpu->pipe_hw);
		goto clean_plane;
	} else if (!pdpu->pipe_hw->cap || !pdpu->pipe_hw->cap->sblk) {
		DPU_ERROR("[%u]SSPP init returned invalid cfg\n", pipe);
		goto clean_sspp;
	}

	/* cache features mask for later */
	pdpu->features = pdpu->pipe_hw->cap->features;
	pdpu->pipe_sblk = pdpu->pipe_hw->cap->sblk;
	if (!pdpu->pipe_sblk) {
		DPU_ERROR("[%u]invalid sblk\n", pipe);
		goto clean_sspp;
	}

	if (pdpu->is_virtual) {
		format_list = pdpu->pipe_sblk->virt_format_list;
		num_formats = pdpu->pipe_sblk->virt_num_formats;
	}
	else {
		format_list = pdpu->pipe_sblk->format_list;
		num_formats = pdpu->pipe_sblk->num_formats;
	}

	ret = drm_universal_plane_init(dev, plane, 0xff, &dpu_plane_funcs,
				format_list, num_formats,
				supported_format_modifiers, type, NULL);
	if (ret)
		goto clean_sspp;

	pdpu->catalog = kms->catalog;

	if (kms->catalog->mixer_count &&
		kms->catalog->mixer[0].sblk->maxblendstages) {
		zpos_max = kms->catalog->mixer[0].sblk->maxblendstages - 1;
		if (zpos_max > DPU_STAGE_MAX - DPU_STAGE_0 - 1)
			zpos_max = DPU_STAGE_MAX - DPU_STAGE_0 - 1;
	}

	ret = drm_plane_create_zpos_property(plane, 0, 0, zpos_max);
	if (ret)
		DPU_ERROR("failed to install zpos property, rc = %d\n", ret);

	drm_plane_create_rotation_property(plane,
			DRM_MODE_ROTATE_0,
			DRM_MODE_ROTATE_0 |
			DRM_MODE_ROTATE_180 |
			DRM_MODE_REFLECT_X |
			DRM_MODE_REFLECT_Y);

	drm_plane_enable_fb_damage_clips(plane);

	/* success! finalize initialization */
	drm_plane_helper_add(plane, &dpu_plane_helper_funcs);

	/* save user friendly pipe name for later */
	snprintf(pdpu->pipe_name, DPU_NAME_SIZE, "plane%u", plane->base.id);

	mutex_init(&pdpu->lock);

	DPU_DEBUG("%s created for pipe:%u id:%u virtual:%u\n", pdpu->pipe_name,
					pipe, plane->base.id, master_plane_id);
	return plane;

clean_sspp:
	if (pdpu && pdpu->pipe_hw)
		dpu_hw_sspp_destroy(pdpu->pipe_hw);
clean_plane:
	kfree(pdpu);
	return ERR_PTR(ret);
}