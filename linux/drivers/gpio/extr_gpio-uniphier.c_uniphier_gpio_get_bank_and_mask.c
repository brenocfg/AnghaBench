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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 unsigned int UNIPHIER_GPIO_LINES_PER_BANK ; 

__attribute__((used)) static void uniphier_gpio_get_bank_and_mask(unsigned int offset,
					    unsigned int *bank, u32 *mask)
{
	*bank = offset / UNIPHIER_GPIO_LINES_PER_BANK;
	*mask = BIT(offset % UNIPHIER_GPIO_LINES_PER_BANK);
}