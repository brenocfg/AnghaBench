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
typedef  int /*<<< orphan*/  uint8_t ;
struct tps6586x_settings {int slew_rate; } ;
struct regulator_init_data {struct tps6586x_settings* driver_data; } ;
struct TYPE_2__ {struct device* parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  TPS6586X_ID_SM_0 129 
#define  TPS6586X_ID_SM_1 128 
 int TPS6586X_SLEW_RATE_MASK ; 
 int TPS6586X_SLEW_RATE_SET ; 
 int /*<<< orphan*/  TPS6586X_SM0SL ; 
 int /*<<< orphan*/  TPS6586X_SM1SL ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int tps6586x_write (struct device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tps6586x_regulator_set_slew_rate(struct platform_device *pdev,
			int id, struct regulator_init_data *p)
{
	struct device *parent = pdev->dev.parent;
	struct tps6586x_settings *setting = p->driver_data;
	uint8_t reg;

	if (setting == NULL)
		return 0;

	if (!(setting->slew_rate & TPS6586X_SLEW_RATE_SET))
		return 0;

	/* only SM0 and SM1 can have the slew rate settings */
	switch (id) {
	case TPS6586X_ID_SM_0:
		reg = TPS6586X_SM0SL;
		break;
	case TPS6586X_ID_SM_1:
		reg = TPS6586X_SM1SL;
		break;
	default:
		dev_err(&pdev->dev, "Only SM0/SM1 can set slew rate\n");
		return -EINVAL;
	}

	return tps6586x_write(parent, reg,
			setting->slew_rate & TPS6586X_SLEW_RATE_MASK);
}