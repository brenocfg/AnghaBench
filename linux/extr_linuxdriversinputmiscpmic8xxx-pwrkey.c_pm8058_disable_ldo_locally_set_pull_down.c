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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int PM8058_REGULATOR_DISABLE ; 
 int PM8058_REGULATOR_ENABLE_MASK ; 
 int PM8058_REGULATOR_PULL_DOWN_EN ; 
 int PM8058_REGULATOR_PULL_DOWN_MASK ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int pm8058_disable_ldo_locally_set_pull_down(struct regmap *regmap,
		u16 ctrl_addr, u16 master_enable_addr, u8 master_enable_bit)
{
	int error;

	/* Enable LDO in master control register. */
	error = regmap_update_bits(regmap, master_enable_addr,
			master_enable_bit, master_enable_bit);
	if (error)
		return error;

	/* Disable LDO in CTRL register and set pull down */
	return regmap_update_bits(regmap, ctrl_addr,
		PM8058_REGULATOR_ENABLE_MASK | PM8058_REGULATOR_PULL_DOWN_MASK,
		PM8058_REGULATOR_DISABLE | PM8058_REGULATOR_PULL_DOWN_EN);
}