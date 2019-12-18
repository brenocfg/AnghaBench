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
struct reg_sequence {int dummy; } ;
struct arizona {int rev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct reg_sequence*) ; 
 int regmap_multi_reg_write_bypassed (int /*<<< orphan*/ ,struct reg_sequence const*,int) ; 
 struct reg_sequence* wm5102_reva_patch ; 
 struct reg_sequence* wm5102_revb_patch ; 

int wm5102_patch(struct arizona *arizona)
{
	const struct reg_sequence *wm5102_patch;
	int patch_size;

	switch (arizona->rev) {
	case 0:
		wm5102_patch = wm5102_reva_patch;
		patch_size = ARRAY_SIZE(wm5102_reva_patch);
		break;
	default:
		wm5102_patch = wm5102_revb_patch;
		patch_size = ARRAY_SIZE(wm5102_revb_patch);
	}

	return regmap_multi_reg_write_bypassed(arizona->regmap,
					       wm5102_patch,
					       patch_size);
}