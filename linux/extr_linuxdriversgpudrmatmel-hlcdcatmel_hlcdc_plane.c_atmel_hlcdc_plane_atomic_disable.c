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
struct drm_plane_state {int dummy; } ;
struct drm_plane {int dummy; } ;
struct atmel_hlcdc_plane {int /*<<< orphan*/  layer; } ;

/* Variables and functions */
 int ATMEL_HLCDC_LAYER_A2Q ; 
 int /*<<< orphan*/  ATMEL_HLCDC_LAYER_CHDR ; 
 int /*<<< orphan*/  ATMEL_HLCDC_LAYER_IDR ; 
 int /*<<< orphan*/  ATMEL_HLCDC_LAYER_ISR ; 
 int ATMEL_HLCDC_LAYER_RST ; 
 int ATMEL_HLCDC_LAYER_UPDATE ; 
 int /*<<< orphan*/  atmel_hlcdc_layer_read_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_hlcdc_layer_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct atmel_hlcdc_plane* drm_plane_to_atmel_hlcdc_plane (struct drm_plane*) ; 

__attribute__((used)) static void atmel_hlcdc_plane_atomic_disable(struct drm_plane *p,
					     struct drm_plane_state *old_state)
{
	struct atmel_hlcdc_plane *plane = drm_plane_to_atmel_hlcdc_plane(p);

	/* Disable interrupts */
	atmel_hlcdc_layer_write_reg(&plane->layer, ATMEL_HLCDC_LAYER_IDR,
				    0xffffffff);

	/* Disable the layer */
	atmel_hlcdc_layer_write_reg(&plane->layer, ATMEL_HLCDC_LAYER_CHDR,
				    ATMEL_HLCDC_LAYER_RST |
				    ATMEL_HLCDC_LAYER_A2Q |
				    ATMEL_HLCDC_LAYER_UPDATE);

	/* Clear all pending interrupts */
	atmel_hlcdc_layer_read_reg(&plane->layer, ATMEL_HLCDC_LAYER_ISR);
}