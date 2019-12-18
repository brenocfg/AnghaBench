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
typedef  scalar_t__ uint32_t ;
struct drm_color_lut {int dummy; } ;
struct dc_transfer_func {scalar_t__ tf; } ;
struct dc_gamma {int /*<<< orphan*/  type; scalar_t__ num_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GAMMA_CS_TFM_1D ; 
 int /*<<< orphan*/  GAMMA_CUSTOM ; 
 scalar_t__ MAX_COLOR_LUT_ENTRIES ; 
 scalar_t__ TRANSFER_FUNCTION_LINEAR ; 
 int /*<<< orphan*/  __drm_lut_to_dc_gamma (struct drm_color_lut const*,struct dc_gamma*,int) ; 
 struct dc_gamma* dc_create_gamma () ; 
 int /*<<< orphan*/  dc_gamma_release (struct dc_gamma**) ; 
 int mod_color_calculate_degamma_params (struct dc_transfer_func*,struct dc_gamma*,int) ; 
 int mod_color_calculate_regamma_params (struct dc_transfer_func*,struct dc_gamma*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __set_output_tf(struct dc_transfer_func *func,
			   const struct drm_color_lut *lut, uint32_t lut_size,
			   bool has_rom)
{
	struct dc_gamma *gamma = NULL;
	bool res;

	ASSERT(lut && lut_size == MAX_COLOR_LUT_ENTRIES);

	gamma = dc_create_gamma();
	if (!gamma)
		return -ENOMEM;

	gamma->num_entries = lut_size;
	__drm_lut_to_dc_gamma(lut, gamma, false);

	if (func->tf == TRANSFER_FUNCTION_LINEAR) {
		/*
		 * Color module doesn't like calculating regamma params
		 * on top of a linear input. But degamma params can be used
		 * instead to simulate this.
		 */
		gamma->type = GAMMA_CUSTOM;
		res = mod_color_calculate_degamma_params(func, gamma, true);
	} else {
		/*
		 * Assume sRGB. The actual mapping will depend on whether the
		 * input was legacy or not.
		 */
		gamma->type = GAMMA_CS_TFM_1D;
		res = mod_color_calculate_regamma_params(func, gamma, false,
							 has_rom, NULL);
	}

	dc_gamma_release(&gamma);

	return res ? 0 : -ENOMEM;
}