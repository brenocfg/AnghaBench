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
struct tps6105x {TYPE_1__* client; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int TPS6105X_REG0_MODE_SHIFT ; 
#define  TPS6105X_REG0_MODE_SHUTDOWN 131 
#define  TPS6105X_REG0_MODE_TORCH 130 
#define  TPS6105X_REG0_MODE_TORCH_FLASH 129 
#define  TPS6105X_REG0_MODE_VOLTAGE 128 
 int /*<<< orphan*/  TPS6105X_REG_0 ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int tps6105x_startup(struct tps6105x *tps6105x)
{
	int ret;
	unsigned int regval;

	ret = regmap_read(tps6105x->regmap, TPS6105X_REG_0, &regval);
	if (ret)
		return ret;
	switch (regval >> TPS6105X_REG0_MODE_SHIFT) {
	case TPS6105X_REG0_MODE_SHUTDOWN:
		dev_info(&tps6105x->client->dev,
			 "TPS6105x found in SHUTDOWN mode\n");
		break;
	case TPS6105X_REG0_MODE_TORCH:
		dev_info(&tps6105x->client->dev,
			 "TPS6105x found in TORCH mode\n");
		break;
	case TPS6105X_REG0_MODE_TORCH_FLASH:
		dev_info(&tps6105x->client->dev,
			 "TPS6105x found in FLASH mode\n");
		break;
	case TPS6105X_REG0_MODE_VOLTAGE:
		dev_info(&tps6105x->client->dev,
			 "TPS6105x found in VOLTAGE mode\n");
		break;
	default:
		break;
	}

	return ret;
}