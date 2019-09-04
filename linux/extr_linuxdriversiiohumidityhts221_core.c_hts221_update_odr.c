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
typedef  scalar_t__ u8 ;
struct hts221_hw {scalar_t__ odr; int /*<<< orphan*/  regmap; } ;
struct TYPE_3__ {scalar_t__ hz; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HTS221_ODR_MASK ; 
 int /*<<< orphan*/  HTS221_REG_CNTRL1_ADDR ; 
 TYPE_1__* hts221_odr_table ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hts221_update_odr(struct hts221_hw *hw, u8 odr)
{
	int i, err;

	for (i = 0; i < ARRAY_SIZE(hts221_odr_table); i++)
		if (hts221_odr_table[i].hz == odr)
			break;

	if (i == ARRAY_SIZE(hts221_odr_table))
		return -EINVAL;

	err = regmap_update_bits(hw->regmap, HTS221_REG_CNTRL1_ADDR,
				 HTS221_ODR_MASK,
				 FIELD_PREP(HTS221_ODR_MASK,
					    hts221_odr_table[i].val));
	if (err < 0)
		return err;

	hw->odr = odr;

	return 0;
}