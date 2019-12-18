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
typedef  int u32 ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int /*<<< orphan*/  GPMC_STATUS ; 
 int gpmc_read_reg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gpmc_gpio_get(struct gpio_chip *chip, unsigned int offset)
{
	u32 reg;

	offset += 8;

	reg = gpmc_read_reg(GPMC_STATUS) & BIT(offset);

	return !!reg;
}