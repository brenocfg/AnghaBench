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
struct bh1770_chip {TYPE_1__* client; scalar_t__ prox_enable_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH1770_ALS_MEAS_RATE ; 
 int i2c_smbus_write_byte_data (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pm_runtime_suspended (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bh1770_lux_rate(struct bh1770_chip *chip, int rate_index)
{
	/* sysfs may call this when the chip is powered off */
	if (pm_runtime_suspended(&chip->client->dev))
		return 0;

	/* Proper proximity response needs fastest lux rate (100ms) */
	if (chip->prox_enable_count)
		rate_index = 0;

	return i2c_smbus_write_byte_data(chip->client,
					BH1770_ALS_MEAS_RATE,
					rate_index);
}