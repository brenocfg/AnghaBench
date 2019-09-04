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
struct zx_vou_hw {scalar_t__ otfppu; scalar_t__ osd; struct device* dev; } ;
struct zx_plane {int /*<<< orphan*/ * bits; scalar_t__ rsz; scalar_t__ hbsc; scalar_t__ layer; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,int) ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_OVERLAY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HBSC_VL_OFFSET (int) ; 
 scalar_t__ OSD_VL_OFFSET (int) ; 
 scalar_t__ RSZ_VL_OFFSET (int) ; 
 int VL_NUM ; 
 struct zx_plane* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int zx_plane_init (struct drm_device*,struct zx_plane*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zx_vl_bits ; 

__attribute__((used)) static void zx_overlay_init(struct drm_device *drm, struct zx_vou_hw *vou)
{
	struct device *dev = vou->dev;
	struct zx_plane *zplane;
	int i;
	int ret;

	/*
	 * VL0 has some quirks on scaling support which need special handling.
	 * Let's leave it out for now.
	 */
	for (i = 1; i < VL_NUM; i++) {
		zplane = devm_kzalloc(dev, sizeof(*zplane), GFP_KERNEL);
		if (!zplane) {
			DRM_DEV_ERROR(dev, "failed to allocate zplane %d\n", i);
			return;
		}

		zplane->layer = vou->osd + OSD_VL_OFFSET(i);
		zplane->hbsc = vou->osd + HBSC_VL_OFFSET(i);
		zplane->rsz = vou->otfppu + RSZ_VL_OFFSET(i);
		zplane->bits = &zx_vl_bits[i];

		ret = zx_plane_init(drm, zplane, DRM_PLANE_TYPE_OVERLAY);
		if (ret) {
			DRM_DEV_ERROR(dev, "failed to init overlay %d\n", i);
			continue;
		}
	}
}