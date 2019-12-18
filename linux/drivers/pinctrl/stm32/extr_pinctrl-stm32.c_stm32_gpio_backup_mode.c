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
typedef  size_t u32 ;
struct stm32_gpio_bank {int* pin_backup; } ;

/* Variables and functions */
 int STM32_GPIO_BKP_ALT_MASK ; 
 size_t STM32_GPIO_BKP_ALT_SHIFT ; 
 int STM32_GPIO_BKP_MODE_MASK ; 
 size_t STM32_GPIO_BKP_MODE_SHIFT ; 

__attribute__((used)) static void stm32_gpio_backup_mode(struct stm32_gpio_bank *bank, u32 offset,
				   u32 mode, u32 alt)
{
	bank->pin_backup[offset] &= ~(STM32_GPIO_BKP_MODE_MASK |
				      STM32_GPIO_BKP_ALT_MASK);
	bank->pin_backup[offset] |= mode << STM32_GPIO_BKP_MODE_SHIFT;
	bank->pin_backup[offset] |= alt << STM32_GPIO_BKP_ALT_SHIFT;
}