#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sec_pmic_dev {scalar_t__ device_type; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap_pmic; TYPE_1__* pdata; } ;
struct TYPE_2__ {scalar_t__ disable_wrstbi; } ;

/* Variables and functions */
 scalar_t__ S2MPS13X ; 
 int /*<<< orphan*/  S2MPS13_REG_WRSTBI ; 
 int /*<<< orphan*/  S2MPS13_REG_WRSTBI_MASK ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sec_pmic_configure(struct sec_pmic_dev *sec_pmic)
{
	int err;

	if (sec_pmic->device_type != S2MPS13X)
		return;

	if (sec_pmic->pdata->disable_wrstbi) {
		/*
		 * If WRSTBI pin is pulled down this feature must be disabled
		 * because each Suspend to RAM will trigger buck voltage reset
		 * to default values.
		 */
		err = regmap_update_bits(sec_pmic->regmap_pmic,
					 S2MPS13_REG_WRSTBI,
					 S2MPS13_REG_WRSTBI_MASK, 0x0);
		if (err)
			dev_warn(sec_pmic->dev,
				 "Cannot initialize WRSTBI config: %d\n",
				 err);
	}
}