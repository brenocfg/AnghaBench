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
struct dc_transfer_func {int dummy; } ;
struct dc_gamma {scalar_t__ num_entries; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GAMMA_RGB_256 ; 
 scalar_t__ MAX_COLOR_LEGACY_LUT_ENTRIES ; 
 int /*<<< orphan*/  __drm_lut_to_dc_gamma (struct drm_color_lut const*,struct dc_gamma*,int) ; 
 struct dc_gamma* dc_create_gamma () ; 
 int mod_color_calculate_regamma_params (struct dc_transfer_func*,struct dc_gamma*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __set_legacy_tf(struct dc_transfer_func *func,
			   const struct drm_color_lut *lut, uint32_t lut_size,
			   bool has_rom)
{
	struct dc_gamma *gamma = NULL;
	bool res;

	ASSERT(lut && lut_size == MAX_COLOR_LEGACY_LUT_ENTRIES);

	gamma = dc_create_gamma();
	if (!gamma)
		return -ENOMEM;

	gamma->type = GAMMA_RGB_256;
	gamma->num_entries = lut_size;
	__drm_lut_to_dc_gamma(lut, gamma, true);

	res = mod_color_calculate_regamma_params(func, gamma, true, has_rom,
						 NULL);

	return res ? 0 : -ENOMEM;
}