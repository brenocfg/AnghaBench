#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct regulator_init_data {int dummy; } ;
struct max8925_platform_data {scalar_t__ ldo20; scalar_t__ ldo19; scalar_t__ ldo18; scalar_t__ ldo17; scalar_t__ ldo16; scalar_t__ ldo15; scalar_t__ ldo14; scalar_t__ ldo13; scalar_t__ ldo12; scalar_t__ ldo11; scalar_t__ ldo10; scalar_t__ ldo9; scalar_t__ ldo8; scalar_t__ ldo7; scalar_t__ ldo6; scalar_t__ ldo5; scalar_t__ ldo4; scalar_t__ ldo3; scalar_t__ ldo2; scalar_t__ ldo1; scalar_t__ sd3; scalar_t__ sd2; scalar_t__ sd1; } ;
struct max8925_chip {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int pdata_size; scalar_t__ platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int mfd_add_devices (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* reg_devs ; 

__attribute__((used)) static void init_regulator(struct max8925_chip *chip,
				     struct max8925_platform_data *pdata)
{
	int ret;

	if (!pdata)
		return;
	if (pdata->sd1) {
		reg_devs[0].platform_data = pdata->sd1;
		reg_devs[0].pdata_size = sizeof(struct regulator_init_data);
	}
	if (pdata->sd2) {
		reg_devs[1].platform_data = pdata->sd2;
		reg_devs[1].pdata_size = sizeof(struct regulator_init_data);
	}
	if (pdata->sd3) {
		reg_devs[2].platform_data = pdata->sd3;
		reg_devs[2].pdata_size = sizeof(struct regulator_init_data);
	}
	if (pdata->ldo1) {
		reg_devs[3].platform_data = pdata->ldo1;
		reg_devs[3].pdata_size = sizeof(struct regulator_init_data);
	}
	if (pdata->ldo2) {
		reg_devs[4].platform_data = pdata->ldo2;
		reg_devs[4].pdata_size = sizeof(struct regulator_init_data);
	}
	if (pdata->ldo3) {
		reg_devs[5].platform_data = pdata->ldo3;
		reg_devs[5].pdata_size = sizeof(struct regulator_init_data);
	}
	if (pdata->ldo4) {
		reg_devs[6].platform_data = pdata->ldo4;
		reg_devs[6].pdata_size = sizeof(struct regulator_init_data);
	}
	if (pdata->ldo5) {
		reg_devs[7].platform_data = pdata->ldo5;
		reg_devs[7].pdata_size = sizeof(struct regulator_init_data);
	}
	if (pdata->ldo6) {
		reg_devs[8].platform_data = pdata->ldo6;
		reg_devs[8].pdata_size = sizeof(struct regulator_init_data);
	}
	if (pdata->ldo7) {
		reg_devs[9].platform_data = pdata->ldo7;
		reg_devs[9].pdata_size = sizeof(struct regulator_init_data);
	}
	if (pdata->ldo8) {
		reg_devs[10].platform_data = pdata->ldo8;
		reg_devs[10].pdata_size = sizeof(struct regulator_init_data);
	}
	if (pdata->ldo9) {
		reg_devs[11].platform_data = pdata->ldo9;
		reg_devs[11].pdata_size = sizeof(struct regulator_init_data);
	}
	if (pdata->ldo10) {
		reg_devs[12].platform_data = pdata->ldo10;
		reg_devs[12].pdata_size = sizeof(struct regulator_init_data);
	}
	if (pdata->ldo11) {
		reg_devs[13].platform_data = pdata->ldo11;
		reg_devs[13].pdata_size = sizeof(struct regulator_init_data);
	}
	if (pdata->ldo12) {
		reg_devs[14].platform_data = pdata->ldo12;
		reg_devs[14].pdata_size = sizeof(struct regulator_init_data);
	}
	if (pdata->ldo13) {
		reg_devs[15].platform_data = pdata->ldo13;
		reg_devs[15].pdata_size = sizeof(struct regulator_init_data);
	}
	if (pdata->ldo14) {
		reg_devs[16].platform_data = pdata->ldo14;
		reg_devs[16].pdata_size = sizeof(struct regulator_init_data);
	}
	if (pdata->ldo15) {
		reg_devs[17].platform_data = pdata->ldo15;
		reg_devs[17].pdata_size = sizeof(struct regulator_init_data);
	}
	if (pdata->ldo16) {
		reg_devs[18].platform_data = pdata->ldo16;
		reg_devs[18].pdata_size = sizeof(struct regulator_init_data);
	}
	if (pdata->ldo17) {
		reg_devs[19].platform_data = pdata->ldo17;
		reg_devs[19].pdata_size = sizeof(struct regulator_init_data);
	}
	if (pdata->ldo18) {
		reg_devs[20].platform_data = pdata->ldo18;
		reg_devs[20].pdata_size = sizeof(struct regulator_init_data);
	}
	if (pdata->ldo19) {
		reg_devs[21].platform_data = pdata->ldo19;
		reg_devs[21].pdata_size = sizeof(struct regulator_init_data);
	}
	if (pdata->ldo20) {
		reg_devs[22].platform_data = pdata->ldo20;
		reg_devs[22].pdata_size = sizeof(struct regulator_init_data);
	}
	ret = mfd_add_devices(chip->dev, 0, reg_devs, ARRAY_SIZE(reg_devs),
			      NULL, 0, NULL);
	if (ret < 0) {
		dev_err(chip->dev, "Failed to add regulator subdev\n");
		return;
	}
}