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
 int /*<<< orphan*/  SUN8I_CSC_CTRL (scalar_t__) ; 
 scalar_t__ SUN8I_CSC_CTRL_EN ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void sun8i_csc_enable(struct regmap *map, u32 base, bool enable)
{
	u32 val;

	if (enable)
		val = SUN8I_CSC_CTRL_EN;
	else
		val = 0;

	regmap_update_bits(map, SUN8I_CSC_CTRL(base), SUN8I_CSC_CTRL_EN, val);
}