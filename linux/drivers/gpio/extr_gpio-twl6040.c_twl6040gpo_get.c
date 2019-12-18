#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct twl6040 {int dummy; } ;
struct gpio_chip {TYPE_1__* parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int /*<<< orphan*/  TWL6040_REG_GPOCTL ; 
 struct twl6040* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int twl6040_reg_read (struct twl6040*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl6040gpo_get(struct gpio_chip *chip, unsigned offset)
{
	struct twl6040 *twl6040 = dev_get_drvdata(chip->parent->parent);
	int ret = 0;

	ret = twl6040_reg_read(twl6040, TWL6040_REG_GPOCTL);
	if (ret < 0)
		return ret;

	return !!(ret & BIT(offset));
}