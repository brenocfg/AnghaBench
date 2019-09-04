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
struct TYPE_4__ {struct atmel_hlcdc_layer_desc* desc; } ;
struct atmel_hlcdc_plane {TYPE_2__ layer; int /*<<< orphan*/  base; } ;
struct TYPE_3__ {scalar_t__ csc; scalar_t__* pstride; scalar_t__* xstride; } ;
struct atmel_hlcdc_layer_desc {scalar_t__ type; TYPE_1__ layout; } ;

/* Variables and functions */
 scalar_t__ ATMEL_HLCDC_CURSOR_LAYER ; 
 scalar_t__ ATMEL_HLCDC_OVERLAY_LAYER ; 
 int DRM_MODE_ROTATE_0 ; 
 int DRM_MODE_ROTATE_180 ; 
 int DRM_MODE_ROTATE_270 ; 
 int DRM_MODE_ROTATE_90 ; 
 int /*<<< orphan*/  atmel_hlcdc_layer_write_cfg (TYPE_2__*,scalar_t__,int) ; 
 int drm_plane_create_alpha_property (int /*<<< orphan*/ *) ; 
 int drm_plane_create_rotation_property (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int atmel_hlcdc_plane_init_properties(struct atmel_hlcdc_plane *plane)
{
	const struct atmel_hlcdc_layer_desc *desc = plane->layer.desc;

	if (desc->type == ATMEL_HLCDC_OVERLAY_LAYER ||
	    desc->type == ATMEL_HLCDC_CURSOR_LAYER) {
		int ret;

		ret = drm_plane_create_alpha_property(&plane->base);
		if (ret)
			return ret;
	}

	if (desc->layout.xstride[0] && desc->layout.pstride[0]) {
		int ret;

		ret = drm_plane_create_rotation_property(&plane->base,
							 DRM_MODE_ROTATE_0,
							 DRM_MODE_ROTATE_0 |
							 DRM_MODE_ROTATE_90 |
							 DRM_MODE_ROTATE_180 |
							 DRM_MODE_ROTATE_270);
		if (ret)
			return ret;
	}

	if (desc->layout.csc) {
		/*
		 * TODO: decare a "yuv-to-rgb-conv-factors" property to let
		 * userspace modify these factors (using a BLOB property ?).
		 */
		atmel_hlcdc_layer_write_cfg(&plane->layer,
					    desc->layout.csc,
					    0x4c900091);
		atmel_hlcdc_layer_write_cfg(&plane->layer,
					    desc->layout.csc + 1,
					    0x7a5f5090);
		atmel_hlcdc_layer_write_cfg(&plane->layer,
					    desc->layout.csc + 2,
					    0x40040890);
	}

	return 0;
}