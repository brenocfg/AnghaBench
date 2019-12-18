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
typedef  int const u32 ;
struct malidp_hw_device {TYPE_1__* hw; } ;
typedef  int s32 ;
struct TYPE_4__ {int se_base; int features; } ;
struct TYPE_3__ {TYPE_2__ map; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int MALIDP_REGMAP_HAS_CLEARIRQ ; 
 int const MALIDP_SE_ENH_COEFF0 ; 
 int /*<<< orphan*/  MALIDP_SE_ENH_HIGH_LEVEL ; 
 int /*<<< orphan*/  MALIDP_SE_ENH_LOW_LEVEL ; 
 int MALIDP_SE_IMAGE_ENH ; 
 int MALIDP_SE_SET_ENH_LIMIT_HIGH (int /*<<< orphan*/ ) ; 
 int MALIDP_SE_SET_ENH_LIMIT_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malidp_hw_write (struct malidp_hw_device*,int const,int const) ; 

__attribute__((used)) static inline void malidp_se_set_enh_coeffs(struct malidp_hw_device *hwdev)
{
	static const s32 enhancer_coeffs[] = {
		-8, -8, -8, -8, 128, -8, -8, -8, -8
	};
	u32 val = MALIDP_SE_SET_ENH_LIMIT_LOW(MALIDP_SE_ENH_LOW_LEVEL) |
		  MALIDP_SE_SET_ENH_LIMIT_HIGH(MALIDP_SE_ENH_HIGH_LEVEL);
	u32 image_enh = hwdev->hw->map.se_base +
			((hwdev->hw->map.features & MALIDP_REGMAP_HAS_CLEARIRQ) ?
			 0x10 : 0xC) + MALIDP_SE_IMAGE_ENH;
	u32 enh_coeffs = image_enh + MALIDP_SE_ENH_COEFF0;
	int i;

	malidp_hw_write(hwdev, val, image_enh);
	for (i = 0; i < ARRAY_SIZE(enhancer_coeffs); ++i)
		malidp_hw_write(hwdev, enhancer_coeffs[i], enh_coeffs + i * 4);
}