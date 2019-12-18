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
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRD_PMIC_EIC_DMSK ; 
 int /*<<< orphan*/  sprd_pmic_eic_update (struct gpio_chip*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sprd_pmic_eic_free(struct gpio_chip *chip, unsigned int offset)
{
	sprd_pmic_eic_update(chip, offset, SPRD_PMIC_EIC_DMSK, 0);
}