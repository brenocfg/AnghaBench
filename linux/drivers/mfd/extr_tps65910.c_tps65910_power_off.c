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
struct tps65910 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVCTRL_DEV_ON_MASK ; 
 int /*<<< orphan*/  DEVCTRL_PWR_OFF_MASK ; 
 int /*<<< orphan*/  TPS65910_DEVCTRL ; 
 struct tps65910* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 TYPE_1__* tps65910_i2c_client ; 
 int /*<<< orphan*/  tps65910_reg_clear_bits (struct tps65910*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tps65910_reg_set_bits (struct tps65910*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tps65910_power_off(void)
{
	struct tps65910 *tps65910;

	tps65910 = dev_get_drvdata(&tps65910_i2c_client->dev);

	if (tps65910_reg_set_bits(tps65910, TPS65910_DEVCTRL,
			DEVCTRL_PWR_OFF_MASK) < 0)
		return;

	tps65910_reg_clear_bits(tps65910, TPS65910_DEVCTRL,
			DEVCTRL_DEV_ON_MASK);
}