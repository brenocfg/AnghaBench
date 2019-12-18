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
typedef  enum sun8i_csc_mode { ____Placeholder_sun8i_csc_mode } sun8i_csc_mode ;
typedef  enum drm_color_range { ____Placeholder_drm_color_range } drm_color_range ;
typedef  enum drm_color_encoding { ____Placeholder_drm_color_encoding } drm_color_encoding ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_WARN (char*) ; 
 int /*<<< orphan*/  SUN8I_CSC_COEFF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  SUN8I_CSC_MODE_YUV2RGB 129 
#define  SUN8I_CSC_MODE_YVU2RGB 128 
 int /*<<< orphan*/  regmap_bulk_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ *** yuv2rgb ; 
 int /*<<< orphan*/ *** yvu2rgb ; 

__attribute__((used)) static void sun8i_csc_set_coefficients(struct regmap *map, u32 base,
				       enum sun8i_csc_mode mode,
				       enum drm_color_encoding encoding,
				       enum drm_color_range range)
{
	const u32 *table;
	u32 base_reg;

	switch (mode) {
	case SUN8I_CSC_MODE_YUV2RGB:
		table = yuv2rgb[range][encoding];
		break;
	case SUN8I_CSC_MODE_YVU2RGB:
		table = yvu2rgb[range][encoding];
		break;
	default:
		DRM_WARN("Wrong CSC mode specified.\n");
		return;
	}

	base_reg = SUN8I_CSC_COEFF(base, 0);
	regmap_bulk_write(map, base_reg, table, 12);
}