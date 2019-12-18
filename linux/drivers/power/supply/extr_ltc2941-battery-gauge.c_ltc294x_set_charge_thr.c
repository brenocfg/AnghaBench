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
typedef  int /*<<< orphan*/  u8 ;
struct ltc294x_info {scalar_t__ Qlsb; int /*<<< orphan*/  client; } ;
typedef  int s32 ;
typedef  enum ltc294x_reg { ____Placeholder_ltc294x_reg } ltc294x_reg ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  I16_LSB (int) ; 
 int /*<<< orphan*/  I16_MSB (int) ; 
 int convert_uAh_to_bin (struct ltc294x_info const*,int) ; 
 int ltc294x_write_regs (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ltc294x_set_charge_thr(const struct ltc294x_info *info,
					enum ltc294x_reg reg, int val)
{
	u8 dataw[2];
	s32 value;

	value = convert_uAh_to_bin(info, val);
	/* Direction depends on how sense+/- were connected */
	if (info->Qlsb < 0)
		value += 0xFFFF;
	if ((value < 0) || (value > 0xFFFF)) /* input validation */
		return -EINVAL;

	/* Set new charge value */
	dataw[0] = I16_MSB(value);
	dataw[1] = I16_LSB(value);
	return ltc294x_write_regs(info->client, reg, &dataw[0], 2);
}