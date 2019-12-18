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
struct sirfsoc_gpio_chip {struct sirfsoc_gpio_bank* sgpio_bank; } ;
struct sirfsoc_gpio_bank {int dummy; } ;

/* Variables and functions */
 unsigned int SIRFSOC_GPIO_BANK_SIZE ; 

__attribute__((used)) static inline struct sirfsoc_gpio_bank *
sirfsoc_gpio_to_bank(struct sirfsoc_gpio_chip *sgpio, unsigned int offset)
{
	return &sgpio->sgpio_bank[offset / SIRFSOC_GPIO_BANK_SIZE];
}