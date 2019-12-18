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
typedef  int /*<<< orphan*/  uint64_t ;
struct ipu_soc {int dummy; } ;
struct ipu_plane {int dma; int dp_flow; int /*<<< orphan*/  base; struct ipu_soc* ipu; } ;
struct drm_device {int dummy; } ;
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int,unsigned int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int DRM_PLANE_TYPE_PRIMARY ; 
 int ENOMEM ; 
 struct ipu_plane* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IPU_DP_FLOW_SYNC_BG ; 
 int IPU_DP_FLOW_SYNC_FG ; 
 int /*<<< orphan*/  drm_plane_create_zpos_immutable_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_plane_create_zpos_property (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_plane_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (struct drm_device*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ipu_format_modifiers ; 
 int /*<<< orphan*/  ipu_plane_formats ; 
 int /*<<< orphan*/  ipu_plane_funcs ; 
 int /*<<< orphan*/  ipu_plane_helper_funcs ; 
 scalar_t__ ipu_prg_present (struct ipu_soc*) ; 
 int /*<<< orphan*/  kfree (struct ipu_plane*) ; 
 struct ipu_plane* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pre_format_modifiers ; 

struct ipu_plane *ipu_plane_init(struct drm_device *dev, struct ipu_soc *ipu,
				 int dma, int dp, unsigned int possible_crtcs,
				 enum drm_plane_type type)
{
	struct ipu_plane *ipu_plane;
	const uint64_t *modifiers = ipu_format_modifiers;
	unsigned int zpos = (type == DRM_PLANE_TYPE_PRIMARY) ? 0 : 1;
	int ret;

	DRM_DEBUG_KMS("channel %d, dp flow %d, possible_crtcs=0x%x\n",
		      dma, dp, possible_crtcs);

	ipu_plane = kzalloc(sizeof(*ipu_plane), GFP_KERNEL);
	if (!ipu_plane) {
		DRM_ERROR("failed to allocate plane\n");
		return ERR_PTR(-ENOMEM);
	}

	ipu_plane->ipu = ipu;
	ipu_plane->dma = dma;
	ipu_plane->dp_flow = dp;

	if (ipu_prg_present(ipu))
		modifiers = pre_format_modifiers;

	ret = drm_universal_plane_init(dev, &ipu_plane->base, possible_crtcs,
				       &ipu_plane_funcs, ipu_plane_formats,
				       ARRAY_SIZE(ipu_plane_formats),
				       modifiers, type, NULL);
	if (ret) {
		DRM_ERROR("failed to initialize plane\n");
		kfree(ipu_plane);
		return ERR_PTR(ret);
	}

	drm_plane_helper_add(&ipu_plane->base, &ipu_plane_helper_funcs);

	if (dp == IPU_DP_FLOW_SYNC_BG || dp == IPU_DP_FLOW_SYNC_FG)
		drm_plane_create_zpos_property(&ipu_plane->base, zpos, 0, 1);
	else
		drm_plane_create_zpos_immutable_property(&ipu_plane->base, 0);

	return ipu_plane;
}