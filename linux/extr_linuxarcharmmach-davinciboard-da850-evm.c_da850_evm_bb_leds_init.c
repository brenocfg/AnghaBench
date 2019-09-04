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
struct gpio_led {unsigned int gpio; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int DA850_EVM_BB_EXP_USER_LED2 ; 
 int DA850_N_BB_USER_LED ; 
 int /*<<< orphan*/ * da850_evm_bb_exp ; 
 struct gpio_led* da850_evm_bb_leds ; 

__attribute__((used)) static void da850_evm_bb_leds_init(unsigned gpio)
{
	int i;
	struct gpio_led *led;

	for (i = 0; i < DA850_N_BB_USER_LED; i++) {
		led = &da850_evm_bb_leds[i];

		led->gpio = gpio + DA850_EVM_BB_EXP_USER_LED2 + i;
		led->name =
			da850_evm_bb_exp[DA850_EVM_BB_EXP_USER_LED2 + i];
	}
}