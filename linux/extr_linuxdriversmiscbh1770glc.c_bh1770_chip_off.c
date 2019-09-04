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
struct bh1770_chip {int /*<<< orphan*/  regs; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BH1770_ALS_CONTROL ; 
 int /*<<< orphan*/  BH1770_DISABLE ; 
 int /*<<< orphan*/  BH1770_INTERRUPT ; 
 int /*<<< orphan*/  BH1770_PS_CONTROL ; 
 int /*<<< orphan*/  BH1770_STANDBY ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bh1770_chip_off(struct bh1770_chip *chip)
{
	i2c_smbus_write_byte_data(chip->client,
					BH1770_INTERRUPT, BH1770_DISABLE);
	i2c_smbus_write_byte_data(chip->client,
				BH1770_ALS_CONTROL, BH1770_STANDBY);
	i2c_smbus_write_byte_data(chip->client,
				BH1770_PS_CONTROL, BH1770_STANDBY);
	regulator_bulk_disable(ARRAY_SIZE(chip->regs), chip->regs);
}