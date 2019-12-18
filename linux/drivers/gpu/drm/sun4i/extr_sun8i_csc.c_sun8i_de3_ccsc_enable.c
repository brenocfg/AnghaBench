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
typedef  scalar_t__ u32 ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE3_BLD_BASE ; 
 int /*<<< orphan*/  SUN50I_MIXER_BLEND_CSC_CTL (int /*<<< orphan*/ ) ; 
 scalar_t__ SUN50I_MIXER_BLEND_CSC_CTL_EN (int) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void sun8i_de3_ccsc_enable(struct regmap *map, int layer, bool enable)
{
	u32 val, mask;

	mask = SUN50I_MIXER_BLEND_CSC_CTL_EN(layer);

	if (enable)
		val = mask;
	else
		val = 0;

	regmap_update_bits(map, SUN50I_MIXER_BLEND_CSC_CTL(DE3_BLD_BASE),
			   mask, val);
}