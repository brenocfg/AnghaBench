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
struct regmap {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable_reg; } ;

/* Variables and functions */
 int ENODEV ; 
 int LM36274_EXT_EN_MASK ; 
#define  LM36274_LDO_NEG 131 
#define  LM36274_LDO_POS 130 
 int LM3632_EXT_EN_MASK ; 
#define  LM3632_LDO_NEG 129 
#define  LM3632_LDO_POS 128 
 TYPE_1__* lm363x_regulator_desc ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int lm363x_regulator_set_ext_en(struct regmap *regmap, int id)
{
	int ext_en_mask = 0;

	switch (id) {
	case LM3632_LDO_POS:
	case LM3632_LDO_NEG:
		ext_en_mask = LM3632_EXT_EN_MASK;
		break;
	case LM36274_LDO_POS:
	case LM36274_LDO_NEG:
		ext_en_mask = LM36274_EXT_EN_MASK;
		break;
	default:
		return -ENODEV;
	}

	return regmap_update_bits(regmap, lm363x_regulator_desc[id].enable_reg,
				 ext_en_mask, ext_en_mask);
}