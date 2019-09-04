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
struct bh1770_chip {int prox_force_update; int /*<<< orphan*/  client; int /*<<< orphan*/  lux_rate_index; scalar_t__ prox_data; scalar_t__ prox_enable_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH1770_DISABLE ; 
 int /*<<< orphan*/  BH1770_ENABLE ; 
 int /*<<< orphan*/  BH1770_PS_CONTROL ; 
 int /*<<< orphan*/  BH1770_STANDALONE ; 
 int /*<<< orphan*/  BH1770_STANDBY ; 
 int /*<<< orphan*/  PROX_BELOW_THRESHOLD ; 
 int /*<<< orphan*/  bh1770_led_cfg (struct bh1770_chip*) ; 
 int /*<<< orphan*/  bh1770_lux_rate (struct bh1770_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bh1770_prox_interrupt_control (struct bh1770_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bh1770_prox_rate (struct bh1770_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bh1770_prox_set_threshold (struct bh1770_chip*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bh1770_prox_mode_control(struct bh1770_chip *chip)
{
	if (chip->prox_enable_count) {
		chip->prox_force_update = true; /* Force immediate update */

		bh1770_lux_rate(chip, chip->lux_rate_index);
		bh1770_prox_set_threshold(chip);
		bh1770_led_cfg(chip);
		bh1770_prox_rate(chip, PROX_BELOW_THRESHOLD);
		bh1770_prox_interrupt_control(chip, BH1770_ENABLE);
		i2c_smbus_write_byte_data(chip->client,
					BH1770_PS_CONTROL, BH1770_STANDALONE);
	} else {
		chip->prox_data = 0;
		bh1770_lux_rate(chip, chip->lux_rate_index);
		bh1770_prox_interrupt_control(chip, BH1770_DISABLE);
		i2c_smbus_write_byte_data(chip->client,
					BH1770_PS_CONTROL, BH1770_STANDBY);
	}
	return 0;
}