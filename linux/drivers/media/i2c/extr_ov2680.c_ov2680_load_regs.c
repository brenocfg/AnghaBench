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
typedef  int /*<<< orphan*/  u16 ;
struct reg_value {int /*<<< orphan*/  val; int /*<<< orphan*/  reg_addr; } ;
struct ov2680_mode_info {unsigned int reg_data_size; struct reg_value* reg_data; } ;
struct ov2680_dev {int dummy; } ;

/* Variables and functions */
 int ov2680_write_reg (struct ov2680_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov2680_load_regs(struct ov2680_dev *sensor,
			    const struct ov2680_mode_info *mode)
{
	const struct reg_value *regs = mode->reg_data;
	unsigned int i;
	int ret = 0;
	u16 reg_addr;
	u8 val;

	for (i = 0; i < mode->reg_data_size; ++i, ++regs) {
		reg_addr = regs->reg_addr;
		val = regs->val;

		ret = ov2680_write_reg(sensor, reg_addr, val);
		if (ret)
			break;
	}

	return ret;
}