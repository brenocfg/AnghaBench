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
struct reset_controller_dev {int dummy; } ;
struct regmap {int dummy; } ;
struct hi6220_reset_data {struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int PERIPH_ASSERT_OFFSET ; 
 int regmap_write (struct regmap*,int,int /*<<< orphan*/ ) ; 
 struct hi6220_reset_data* to_reset_data (struct reset_controller_dev*) ; 

__attribute__((used)) static int hi6220_peripheral_assert(struct reset_controller_dev *rc_dev,
				    unsigned long idx)
{
	struct hi6220_reset_data *data = to_reset_data(rc_dev);
	struct regmap *regmap = data->regmap;
	u32 bank = idx >> 8;
	u32 offset = idx & 0xff;
	u32 reg = PERIPH_ASSERT_OFFSET + bank * 0x10;

	return regmap_write(regmap, reg, BIT(offset));
}