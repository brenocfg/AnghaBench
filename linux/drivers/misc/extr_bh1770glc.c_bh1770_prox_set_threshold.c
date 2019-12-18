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
typedef  int /*<<< orphan*/  u8 ;
struct bh1770_chip {TYPE_1__* client; int /*<<< orphan*/  prox_threshold_hw; int /*<<< orphan*/  prox_threshold; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH1770_PS_TH_LED1 ; 
 int /*<<< orphan*/  bh1770_psadjusted_to_raw (struct bh1770_chip*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pm_runtime_suspended (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bh1770_prox_set_threshold(struct bh1770_chip *chip)
{
	u8 tmp = 0;

	/* sysfs may call this when the chip is powered off */
	if (pm_runtime_suspended(&chip->client->dev))
		return 0;

	tmp = bh1770_psadjusted_to_raw(chip, chip->prox_threshold);
	chip->prox_threshold_hw = tmp;

	return	i2c_smbus_write_byte_data(chip->client, BH1770_PS_TH_LED1,
					tmp);
}