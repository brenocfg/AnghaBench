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
typedef  int /*<<< orphan*/  u16 ;
struct lan9303 {int dummy; } ;

/* Variables and functions */
 int lan9303_read_switch_reg (struct lan9303*,int /*<<< orphan*/ ,int*) ; 
 int lan9303_write_switch_reg (struct lan9303*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lan9303_write_switch_reg_mask(struct lan9303 *chip, u16 regnum,
					 u32 val, u32 mask)
{
	int ret;
	u32 reg;

	ret = lan9303_read_switch_reg(chip, regnum, &reg);
	if (ret)
		return ret;

	reg = (reg & ~mask) | val;

	return lan9303_write_switch_reg(chip, regnum, reg);
}