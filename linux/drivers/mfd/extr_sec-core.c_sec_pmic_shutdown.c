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
struct sec_pmic_dev {int device_type; int /*<<< orphan*/  regmap_pmic; int /*<<< orphan*/  dev; TYPE_1__* pdata; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  manual_poweroff; } ;

/* Variables and functions */
#define  S2MPS11X 128 
 unsigned int S2MPS11_CTRL1_PWRHOLD_MASK ; 
 unsigned int S2MPS11_REG_CTRL1 ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 struct sec_pmic_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sec_pmic_shutdown(struct i2c_client *i2c)
{
	struct sec_pmic_dev *sec_pmic = i2c_get_clientdata(i2c);
	unsigned int reg, mask;

	if (!sec_pmic->pdata->manual_poweroff)
		return;

	switch (sec_pmic->device_type) {
	case S2MPS11X:
		reg = S2MPS11_REG_CTRL1;
		mask = S2MPS11_CTRL1_PWRHOLD_MASK;
		break;
	default:
		/*
		 * Currently only one board with S2MPS11 needs this, so just
		 * ignore the rest.
		 */
		dev_warn(sec_pmic->dev,
			"Unsupported device %lu for manual power off\n",
			sec_pmic->device_type);
		return;
	}

	regmap_update_bits(sec_pmic->regmap_pmic, reg, mask, 0);
}