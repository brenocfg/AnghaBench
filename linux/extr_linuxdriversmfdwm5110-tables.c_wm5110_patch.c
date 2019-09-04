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
struct arizona {int rev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int regmap_register_patch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm5110_reva_patch ; 
 int /*<<< orphan*/  wm5110_revb_patch ; 
 int /*<<< orphan*/  wm5110_revd_patch ; 
 int /*<<< orphan*/  wm5110_reve_patch ; 

int wm5110_patch(struct arizona *arizona)
{
	switch (arizona->rev) {
	case 0:
		return regmap_register_patch(arizona->regmap,
					     wm5110_reva_patch,
					     ARRAY_SIZE(wm5110_reva_patch));
	case 1:
		return regmap_register_patch(arizona->regmap,
					     wm5110_revb_patch,
					     ARRAY_SIZE(wm5110_revb_patch));
	case 3:
		return regmap_register_patch(arizona->regmap,
					     wm5110_revd_patch,
					     ARRAY_SIZE(wm5110_revd_patch));
	default:
		return regmap_register_patch(arizona->regmap,
					     wm5110_reve_patch,
					     ARRAY_SIZE(wm5110_reve_patch));
	}
}