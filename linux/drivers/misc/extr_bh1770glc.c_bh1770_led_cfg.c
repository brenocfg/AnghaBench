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
struct bh1770_chip {int prox_led; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH1770_I_LED ; 
 int BH1770_LED1 ; 
 int BH1770_LED_5mA ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int bh1770_led_cfg(struct bh1770_chip *chip)
{
	/* LED cfg, current for leds 1 and 2 */
	return i2c_smbus_write_byte_data(chip->client,
					BH1770_I_LED,
					(BH1770_LED1 << 6) |
					(BH1770_LED_5mA << 3) |
					chip->prox_led);
}