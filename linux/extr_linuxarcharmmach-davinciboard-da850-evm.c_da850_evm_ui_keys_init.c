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
struct gpio_keys_button {unsigned int gpio; int /*<<< orphan*/  desc; scalar_t__ code; } ;

/* Variables and functions */
 int DA850_EVM_UI_EXP_PB8 ; 
 int DA850_N_UI_PB ; 
 scalar_t__ KEY_F8 ; 
 int /*<<< orphan*/ * da850_evm_ui_exp ; 
 struct gpio_keys_button* da850_evm_ui_keys ; 

__attribute__((used)) static void da850_evm_ui_keys_init(unsigned gpio)
{
	int i;
	struct gpio_keys_button *button;

	for (i = 0; i < DA850_N_UI_PB; i++) {
		button = &da850_evm_ui_keys[i];
		button->code = KEY_F8 - i;
		button->desc = da850_evm_ui_exp[DA850_EVM_UI_EXP_PB8 + i];
		button->gpio = gpio + DA850_EVM_UI_EXP_PB8 + i;
	}
}