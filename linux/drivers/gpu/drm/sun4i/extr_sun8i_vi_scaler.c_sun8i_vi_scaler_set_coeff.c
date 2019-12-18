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
typedef  int /*<<< orphan*/  u32 ;
struct regmap {int dummy; } ;
struct drm_format_info {int hsub; int vsub; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUN8I_SCALER_VSU_CHCOEFF0 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SUN8I_SCALER_VSU_CHCOEFF1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SUN8I_SCALER_VSU_CVCOEFF (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SUN8I_SCALER_VSU_YHCOEFF0 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SUN8I_SCALER_VSU_YHCOEFF1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SUN8I_SCALER_VSU_YVCOEFF (int /*<<< orphan*/ ,int) ; 
 int SUN8I_VI_SCALER_COEFF_COUNT ; 
 int /*<<< orphan*/ * bicubic4coefftab32 ; 
 int /*<<< orphan*/ * bicubic8coefftab32_left ; 
 int /*<<< orphan*/ * bicubic8coefftab32_right ; 
 int /*<<< orphan*/  const* lan2coefftab32 ; 
 int /*<<< orphan*/  const* lan3coefftab32_left ; 
 int /*<<< orphan*/  const* lan3coefftab32_right ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int sun8i_vi_scaler_coef_index (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun8i_vi_scaler_set_coeff(struct regmap *map, u32 base,
				      u32 hstep, u32 vstep,
				      const struct drm_format_info *format)
{
	const u32 *ch_left, *ch_right, *cy;
	int offset, i;

	if (format->hsub == 1 && format->vsub == 1) {
		ch_left = lan3coefftab32_left;
		ch_right = lan3coefftab32_right;
		cy = lan2coefftab32;
	} else {
		ch_left = bicubic8coefftab32_left;
		ch_right = bicubic8coefftab32_right;
		cy = bicubic4coefftab32;
	}

	offset = sun8i_vi_scaler_coef_index(hstep) *
			SUN8I_VI_SCALER_COEFF_COUNT;
	for (i = 0; i < SUN8I_VI_SCALER_COEFF_COUNT; i++) {
		regmap_write(map, SUN8I_SCALER_VSU_YHCOEFF0(base, i),
			     lan3coefftab32_left[offset + i]);
		regmap_write(map, SUN8I_SCALER_VSU_YHCOEFF1(base, i),
			     lan3coefftab32_right[offset + i]);
		regmap_write(map, SUN8I_SCALER_VSU_CHCOEFF0(base, i),
			     ch_left[offset + i]);
		regmap_write(map, SUN8I_SCALER_VSU_CHCOEFF1(base, i),
			     ch_right[offset + i]);
	}

	offset = sun8i_vi_scaler_coef_index(hstep) *
			SUN8I_VI_SCALER_COEFF_COUNT;
	for (i = 0; i < SUN8I_VI_SCALER_COEFF_COUNT; i++) {
		regmap_write(map, SUN8I_SCALER_VSU_YVCOEFF(base, i),
			     lan2coefftab32[offset + i]);
		regmap_write(map, SUN8I_SCALER_VSU_CVCOEFF(base, i),
			     cy[offset + i]);
	}
}