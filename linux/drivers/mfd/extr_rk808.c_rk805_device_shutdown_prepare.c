#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rk808 {int /*<<< orphan*/  regmap; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RK805_GPIO_IO_POL_REG ; 
 int /*<<< orphan*/  SHUTDOWN_FUN ; 
 int /*<<< orphan*/  SLP_SD_MSK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct rk808* i2c_get_clientdata (TYPE_1__*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* rk808_i2c_client ; 

__attribute__((used)) static void rk805_device_shutdown_prepare(void)
{
	int ret;
	struct rk808 *rk808 = i2c_get_clientdata(rk808_i2c_client);

	if (!rk808)
		return;

	ret = regmap_update_bits(rk808->regmap,
				 RK805_GPIO_IO_POL_REG,
				 SLP_SD_MSK, SHUTDOWN_FUN);
	if (ret)
		dev_err(&rk808_i2c_client->dev, "Failed to shutdown device!\n");
}