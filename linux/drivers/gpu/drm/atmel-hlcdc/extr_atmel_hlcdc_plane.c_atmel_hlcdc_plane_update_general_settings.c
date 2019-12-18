#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct drm_format_info {scalar_t__ format; scalar_t__ has_alpha; } ;
struct TYPE_8__ {int /*<<< orphan*/  alpha; TYPE_1__* fb; } ;
struct atmel_hlcdc_plane_state {unsigned int ahb_id; scalar_t__ disc_w; scalar_t__ disc_h; TYPE_3__ base; } ;
struct TYPE_10__ {struct atmel_hlcdc_layer_desc* desc; } ;
struct TYPE_7__ {scalar_t__ type; } ;
struct atmel_hlcdc_plane {TYPE_5__ layer; TYPE_2__ base; } ;
struct TYPE_9__ {int /*<<< orphan*/  general_config; } ;
struct atmel_hlcdc_layer_desc {TYPE_4__ layout; } ;
struct TYPE_6__ {struct drm_format_info* format; } ;

/* Variables and functions */
 unsigned int ATMEL_HLCDC_LAYER_DISCEN ; 
 unsigned int ATMEL_HLCDC_LAYER_DMA ; 
 unsigned int ATMEL_HLCDC_LAYER_DMA_BLEN_INCR16 ; 
 int /*<<< orphan*/  ATMEL_HLCDC_LAYER_DMA_CFG ; 
 unsigned int ATMEL_HLCDC_LAYER_DMA_ROTDIS ; 
 unsigned int ATMEL_HLCDC_LAYER_GA (int /*<<< orphan*/ ) ; 
 unsigned int ATMEL_HLCDC_LAYER_GAEN ; 
 unsigned int ATMEL_HLCDC_LAYER_ITER ; 
 unsigned int ATMEL_HLCDC_LAYER_ITER2BL ; 
 unsigned int ATMEL_HLCDC_LAYER_LAEN ; 
 unsigned int ATMEL_HLCDC_LAYER_OVR ; 
 unsigned int ATMEL_HLCDC_LAYER_REP ; 
 scalar_t__ DRM_FORMAT_RGB888 ; 
 scalar_t__ DRM_PLANE_TYPE_PRIMARY ; 
 int /*<<< orphan*/  atmel_hlcdc_layer_write_cfg (TYPE_5__*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
atmel_hlcdc_plane_update_general_settings(struct atmel_hlcdc_plane *plane,
					struct atmel_hlcdc_plane_state *state)
{
	unsigned int cfg = ATMEL_HLCDC_LAYER_DMA_BLEN_INCR16 | state->ahb_id;
	const struct atmel_hlcdc_layer_desc *desc = plane->layer.desc;
	const struct drm_format_info *format = state->base.fb->format;

	/*
	 * Rotation optimization is not working on RGB888 (rotation is still
	 * working but without any optimization).
	 */
	if (format->format == DRM_FORMAT_RGB888)
		cfg |= ATMEL_HLCDC_LAYER_DMA_ROTDIS;

	atmel_hlcdc_layer_write_cfg(&plane->layer, ATMEL_HLCDC_LAYER_DMA_CFG,
				    cfg);

	cfg = ATMEL_HLCDC_LAYER_DMA | ATMEL_HLCDC_LAYER_REP;

	if (plane->base.type != DRM_PLANE_TYPE_PRIMARY) {
		cfg |= ATMEL_HLCDC_LAYER_OVR | ATMEL_HLCDC_LAYER_ITER2BL |
		       ATMEL_HLCDC_LAYER_ITER;

		if (format->has_alpha)
			cfg |= ATMEL_HLCDC_LAYER_LAEN;
		else
			cfg |= ATMEL_HLCDC_LAYER_GAEN |
			       ATMEL_HLCDC_LAYER_GA(state->base.alpha);
	}

	if (state->disc_h && state->disc_w)
		cfg |= ATMEL_HLCDC_LAYER_DISCEN;

	atmel_hlcdc_layer_write_cfg(&plane->layer, desc->layout.general_config,
				    cfg);
}