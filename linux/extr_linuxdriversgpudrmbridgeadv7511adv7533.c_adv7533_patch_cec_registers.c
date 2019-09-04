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
struct adv7511 {int /*<<< orphan*/  regmap_cec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adv7533_cec_fixed_registers ; 
 int regmap_register_patch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int adv7533_patch_cec_registers(struct adv7511 *adv)
{
	return regmap_register_patch(adv->regmap_cec,
				    adv7533_cec_fixed_registers,
				    ARRAY_SIZE(adv7533_cec_fixed_registers));
}