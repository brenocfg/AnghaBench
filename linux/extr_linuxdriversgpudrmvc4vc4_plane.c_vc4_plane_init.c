#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ u32 ;
struct drm_plane {int dummy; } ;
struct vc4_plane {struct drm_plane base; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;
struct TYPE_3__ {scalar_t__ hvs; scalar_t__ drm; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
#define  DRM_FORMAT_MOD_BROADCOM_SAND128 133 
#define  DRM_FORMAT_MOD_BROADCOM_SAND256 132 
#define  DRM_FORMAT_MOD_BROADCOM_SAND64 131 
#define  DRM_FORMAT_MOD_BROADCOM_VC4_T_TILED 130 
#define  DRM_FORMAT_MOD_INVALID 129 
#define  DRM_FORMAT_MOD_LINEAR 128 
 int DRM_PLANE_TYPE_CURSOR ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct drm_plane* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HVS_PIXEL_FORMAT_YCBCR_YUV420_3PLANE ; 
 struct vc4_plane* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_plane_create_alpha_property (struct drm_plane*) ; 
 int /*<<< orphan*/  drm_plane_helper_add (struct drm_plane*,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (struct drm_device*,struct drm_plane*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,scalar_t__,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* hvs_formats ; 
 int /*<<< orphan*/  vc4_plane_funcs ; 
 int /*<<< orphan*/  vc4_plane_helper_funcs ; 

struct drm_plane *vc4_plane_init(struct drm_device *dev,
				 enum drm_plane_type type)
{
	struct drm_plane *plane = NULL;
	struct vc4_plane *vc4_plane;
	u32 formats[ARRAY_SIZE(hvs_formats)];
	u32 num_formats = 0;
	int ret = 0;
	unsigned i;
	static const uint64_t modifiers[] = {
		DRM_FORMAT_MOD_BROADCOM_VC4_T_TILED,
		DRM_FORMAT_MOD_BROADCOM_SAND128,
		DRM_FORMAT_MOD_BROADCOM_SAND64,
		DRM_FORMAT_MOD_BROADCOM_SAND256,
		DRM_FORMAT_MOD_LINEAR,
		DRM_FORMAT_MOD_INVALID
	};

	vc4_plane = devm_kzalloc(dev->dev, sizeof(*vc4_plane),
				 GFP_KERNEL);
	if (!vc4_plane)
		return ERR_PTR(-ENOMEM);

	for (i = 0; i < ARRAY_SIZE(hvs_formats); i++) {
		/* Don't allow YUV in cursor planes, since that means
		 * tuning on the scaler, which we don't allow for the
		 * cursor.
		 */
		if (type != DRM_PLANE_TYPE_CURSOR ||
		    hvs_formats[i].hvs < HVS_PIXEL_FORMAT_YCBCR_YUV420_3PLANE) {
			formats[num_formats++] = hvs_formats[i].drm;
		}
	}
	plane = &vc4_plane->base;
	ret = drm_universal_plane_init(dev, plane, 0,
				       &vc4_plane_funcs,
				       formats, num_formats,
				       modifiers, type, NULL);

	drm_plane_helper_add(plane, &vc4_plane_helper_funcs);

	drm_plane_create_alpha_property(plane);

	return plane;
}