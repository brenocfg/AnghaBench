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
typedef  int u32 ;
struct regmap {int dummy; } ;
typedef  enum sun8i_csc_mode { ____Placeholder_sun8i_csc_mode } sun8i_csc_mode ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_WARN (char*) ; 
 int /*<<< orphan*/  SUN8I_CSC_COEFF (int,int) ; 
#define  SUN8I_CSC_MODE_YUV2RGB 129 
#define  SUN8I_CSC_MODE_YVU2RGB 128 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 
 int* yuv2rgb ; 
 int* yvu2rgb ; 

__attribute__((used)) static void sun8i_csc_set_coefficients(struct regmap *map, u32 base,
				       enum sun8i_csc_mode mode)
{
	const u32 *table;
	int i, data;

	switch (mode) {
	case SUN8I_CSC_MODE_YUV2RGB:
		table = yuv2rgb;
		break;
	case SUN8I_CSC_MODE_YVU2RGB:
		table = yvu2rgb;
		break;
	default:
		DRM_WARN("Wrong CSC mode specified.\n");
		return;
	}

	for (i = 0; i < 12; i++) {
		data = table[i];
		/* For some reason, 0x200 must be added to constant parts */
		if (((i + 1) & 3) == 0)
			data += 0x200;
		regmap_write(map, SUN8I_CSC_COEFF(base, i), data);
	}
}