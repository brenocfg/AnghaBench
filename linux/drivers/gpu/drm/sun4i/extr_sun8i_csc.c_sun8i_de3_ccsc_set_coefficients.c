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
 int /*<<< orphan*/  DE3_BLD_BASE ; 
 int /*<<< orphan*/  DRM_WARN (char*) ; 
 int /*<<< orphan*/  SUN50I_MIXER_BLEND_CSC_COEFF (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  SUN8I_CSC_MODE_YUV2RGB 129 
#define  SUN8I_CSC_MODE_YVU2RGB 128 
 int /*<<< orphan*/  regmap_bulk_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ *** yuv2rgb_de3 ; 
 int /*<<< orphan*/ *** yvu2rgb_de3 ; 

__attribute__((used)) static void sun8i_de3_ccsc_set_coefficients(struct regmap *map, int layer,
					    enum sun8i_csc_mode mode,
					    enum drm_color_encoding encoding,
					    enum drm_color_range range)
{
	const u32 *table;
	u32 base_reg;

	switch (mode) {
	case SUN8I_CSC_MODE_YUV2RGB:
		table = yuv2rgb_de3[range][encoding];
		break;
	case SUN8I_CSC_MODE_YVU2RGB:
		table = yvu2rgb_de3[range][encoding];
		break;
	default:
		DRM_WARN("Wrong CSC mode specified.\n");
		return;
	}

	base_reg = SUN50I_MIXER_BLEND_CSC_COEFF(DE3_BLD_BASE, layer, 0, 0);
	regmap_bulk_write(map, base_reg, table, 12);
}