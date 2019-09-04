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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct reg_value {int delay_ms; scalar_t__ mask; scalar_t__ val; int /*<<< orphan*/  reg_addr; } ;
struct ov5640_mode_info {unsigned int reg_data_size; struct reg_value* reg_data; } ;
struct ov5640_dev {int dummy; } ;

/* Variables and functions */
 int ov5640_mod_reg (struct ov5640_dev*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int ov5640_set_timings (struct ov5640_dev*,struct ov5640_mode_info const*) ; 
 int ov5640_write_reg (struct ov5640_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ov5640_load_regs(struct ov5640_dev *sensor,
			    const struct ov5640_mode_info *mode)
{
	const struct reg_value *regs = mode->reg_data;
	unsigned int i;
	u32 delay_ms;
	u16 reg_addr;
	u8 mask, val;
	int ret = 0;

	for (i = 0; i < mode->reg_data_size; ++i, ++regs) {
		delay_ms = regs->delay_ms;
		reg_addr = regs->reg_addr;
		val = regs->val;
		mask = regs->mask;

		if (mask)
			ret = ov5640_mod_reg(sensor, reg_addr, mask, val);
		else
			ret = ov5640_write_reg(sensor, reg_addr, val);
		if (ret)
			break;

		if (delay_ms)
			usleep_range(1000 * delay_ms, 1000 * delay_ms + 100);
	}

	return ov5640_set_timings(sensor, mode);
}