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
struct gpio_keys_button {unsigned int gpio; void* desc; scalar_t__ code; } ;

/* Variables and functions */
 size_t DA850_EVM_BB_EXP_USER_PB1 ; 
 int DA850_EVM_BB_EXP_USER_SW1 ; 
 int DA850_N_BB_USER_SW ; 
 scalar_t__ SW_LID ; 
 void** da850_evm_bb_exp ; 
 struct gpio_keys_button* da850_evm_bb_keys ; 

__attribute__((used)) static void da850_evm_bb_keys_init(unsigned gpio)
{
	int i;
	struct gpio_keys_button *button;

	button = &da850_evm_bb_keys[0];
	button->desc = da850_evm_bb_exp[DA850_EVM_BB_EXP_USER_PB1];
	button->gpio = gpio + DA850_EVM_BB_EXP_USER_PB1;

	for (i = 0; i < DA850_N_BB_USER_SW; i++) {
		button = &da850_evm_bb_keys[i + 1];
		button->code = SW_LID + i;
		button->desc = da850_evm_bb_exp[DA850_EVM_BB_EXP_USER_SW1 + i];
		button->gpio = gpio + DA850_EVM_BB_EXP_USER_SW1 + i;
	}
}