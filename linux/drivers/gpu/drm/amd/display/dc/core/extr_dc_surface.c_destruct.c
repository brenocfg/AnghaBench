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
struct dc_plane_state {int /*<<< orphan*/ * blend_tf; int /*<<< orphan*/ * lut3d_func; int /*<<< orphan*/ * in_shaper_func; int /*<<< orphan*/ * in_transfer_func; int /*<<< orphan*/ * gamma_correction; } ;

/* Variables and functions */
 int /*<<< orphan*/  dc_3dlut_func_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dc_gamma_release (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dc_transfer_func_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destruct(struct dc_plane_state *plane_state)
{
	if (plane_state->gamma_correction != NULL) {
		dc_gamma_release(&plane_state->gamma_correction);
	}
	if (plane_state->in_transfer_func != NULL) {
		dc_transfer_func_release(
				plane_state->in_transfer_func);
		plane_state->in_transfer_func = NULL;
	}
#if defined(CONFIG_DRM_AMD_DC_DCN2_0)
	if (plane_state->in_shaper_func != NULL) {
		dc_transfer_func_release(
				plane_state->in_shaper_func);
		plane_state->in_shaper_func = NULL;
	}
	if (plane_state->lut3d_func != NULL) {
		dc_3dlut_func_release(
				plane_state->lut3d_func);
		plane_state->lut3d_func = NULL;
	}
	if (plane_state->blend_tf != NULL) {
		dc_transfer_func_release(
				plane_state->blend_tf);
		plane_state->blend_tf = NULL;
	}

#endif
}