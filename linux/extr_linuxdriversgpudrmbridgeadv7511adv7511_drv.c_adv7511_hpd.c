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
struct adv7511 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int ADV7511_INT0_HPD ; 
 int /*<<< orphan*/  ADV7511_REG_INT (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static bool adv7511_hpd(struct adv7511 *adv7511)
{
	unsigned int irq0;
	int ret;

	ret = regmap_read(adv7511->regmap, ADV7511_REG_INT(0), &irq0);
	if (ret < 0)
		return false;

	if (irq0 & ADV7511_INT0_HPD) {
		regmap_write(adv7511->regmap, ADV7511_REG_INT(0),
			     ADV7511_INT0_HPD);
		return true;
	}

	return false;
}