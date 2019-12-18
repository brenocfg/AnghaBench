#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct TYPE_3__ {unsigned int pin; int /*<<< orphan*/  offset; int /*<<< orphan*/  bit; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 TYPE_1__* mt2701_spec_pinmux ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void mt2701_spec_pinmux_set(struct regmap *reg, unsigned int pin,
			unsigned int mode)
{
	unsigned int i, value, mask;
	unsigned int info_num = ARRAY_SIZE(mt2701_spec_pinmux);
	unsigned int spec_flag;

	for (i = 0; i < info_num; i++) {
		if (pin == mt2701_spec_pinmux[i].pin)
			break;
	}

	if (i == info_num)
		return;

	spec_flag = (mode >> 3);
	mask = BIT(mt2701_spec_pinmux[i].bit);
	if (!spec_flag)
		value = mask;
	else
		value = 0;
	regmap_update_bits(reg, mt2701_spec_pinmux[i].offset, mask, value);
}