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
struct dpu_plane {int pipe; int is_virtual; int features; TYPE_6__* pipe_hw; int /*<<< orphan*/  pipe_name; int /*<<< orphan*/  lock; TYPE_7__* catalog; int /*<<< orphan*/  nformats; int /*<<< orphan*/  formats; TYPE_2__* pipe_sblk; int /*<<< orphan*/  mplane_list; struct drm_plane base; } ;
struct dpu_kms {TYPE_7__* catalog; int /*<<< orphan*/  mmio; } ;
struct dpu_format_extended {int dummy; } ;
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;
struct TYPE_17__ {TYPE_4__* mixer; scalar_t__ mixer_count; } ;
struct TYPE_16__ {TYPE_1__* cap; } ;
struct TYPE_14__ {TYPE_3__* sblk; } ;
struct TYPE_13__ {int maxblendstages; } ;
struct TYPE_12__ {struct dpu_format_extended* virt_format_list; struct dpu_format_extended* format_list; } ;
struct TYPE_11__ {int features; TYPE_2__* sblk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPU_DEBUG (char*,int /*<<< orphan*/ ,int,int,scalar_t__) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,int) ; 
 int /*<<< orphan*/  DPU_NAME_SIZE ; 
 int /*<<< orphan*/  DPU_SSPP_CURSOR ; 
 int DPU_STAGE_0 ; 
 int DPU_STAGE_MAX ; 
 int DPU_ZPOS_MAX ; 
 int DRM_PLANE_TYPE_CURSOR ; 
 int DRM_PLANE_TYPE_OVERLAY ; 
 int DRM_PLANE_TYPE_PRIMARY ; 
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
 int /*<<< orphan*/  dpu_populate_formats (struct dpu_format_extended const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_plane_create_zpos_property (struct drm_plane*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct drm_plane* drm_plane_find (struct drm_device*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  drm_plane_helper_add (struct drm_plane*,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (struct drm_device*,struct drm_plane*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dpu_plane*) ; 
 struct dpu_plane* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 struct dpu_kms* to_dpu_kms (int /*<<< orphan*/ ) ; 
 struct dpu_plane* to_dpu_plane (struct drm_plane*) ; 

struct drm_plane *dpu_plane_init(struct drm_device *dev,
		uint32_t pipe, bool primary_plane,
		unsigned long possible_crtcs, u32 master_plane_id)
{
	struct drm_plane *plane = NULL, *master_plane = NULL;
	const struct dpu_format_extended *format_list;
	struct dpu_plane *pdpu;
	struct msm_drm_private *priv;
	struct dpu_kms *kms;
	enum drm_plane_type type;
	int zpos_max = DPU_ZPOS_MAX;
	int ret = -EINVAL;

	if (!dev) {
		DPU_ERROR("[%u]device is NULL\n", pipe);
		goto exit;
	}

	priv = dev->dev_private;
	if (!priv) {
		DPU_ERROR("[%u]private data is NULL\n", pipe);
		goto exit;
	}

	if (!priv->kms) {
		DPU_ERROR("[%u]invalid KMS reference\n", pipe);
		goto exit;
	}
	kms = to_dpu_kms(priv->kms);

	if (!kms->catalog) {
		DPU_ERROR("[%u]invalid catalog reference\n", pipe);
		goto exit;
	}

	/* create and zero local structure */
	pdpu = kzalloc(sizeof(*pdpu), GFP_KERNEL);
	if (!pdpu) {
		DPU_ERROR("[%u]failed to allocate local plane struct\n", pipe);
		ret = -ENOMEM;
		goto exit;
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

	if (!master_plane_id)
		format_list = pdpu->pipe_sblk->format_list;
	else
		format_list = pdpu->pipe_sblk->virt_format_list;

	pdpu->nformats = dpu_populate_formats(format_list,
				pdpu->formats,
				0,
				ARRAY_SIZE(pdpu->formats));

	if (!pdpu->nformats) {
		DPU_ERROR("[%u]no valid formats for plane\n", pipe);
		goto clean_sspp;
	}

	if (pdpu->features & BIT(DPU_SSPP_CURSOR))
		type = DRM_PLANE_TYPE_CURSOR;
	else if (primary_plane)
		type = DRM_PLANE_TYPE_PRIMARY;
	else
		type = DRM_PLANE_TYPE_OVERLAY;
	ret = drm_universal_plane_init(dev, plane, 0xff, &dpu_plane_funcs,
				pdpu->formats, pdpu->nformats,
				NULL, type, NULL);
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
exit:
	return ERR_PTR(ret);
}