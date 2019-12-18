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
struct atmel_pioctrl {scalar_t__ reg_base; } ;

/* Variables and functions */
 unsigned int ATMEL_PIO_BANK_OFFSET ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

__attribute__((used)) static void atmel_gpio_write(struct atmel_pioctrl *atmel_pioctrl,
			     unsigned int bank, unsigned int reg,
			     unsigned int val)
{
	writel_relaxed(val, atmel_pioctrl->reg_base
		       + ATMEL_PIO_BANK_OFFSET * bank + reg);
}