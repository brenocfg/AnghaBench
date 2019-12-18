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
struct f71805f_data {int* fan_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  F71805F_REG_FAN_CTRL (int) ; 
 int /*<<< orphan*/  F71805F_REG_START ; 
 int FAN_CTRL_LATCH_FULL ; 
 void* f71805f_read8 (struct f71805f_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f71805f_write8 (struct f71805f_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void f71805f_init_device(struct f71805f_data *data)
{
	u8 reg;
	int i;

	reg = f71805f_read8(data, F71805F_REG_START);
	if ((reg & 0x41) != 0x01) {
		pr_debug("Starting monitoring operations\n");
		f71805f_write8(data, F71805F_REG_START, (reg | 0x01) & ~0x40);
	}

	/*
	 * Fan monitoring can be disabled. If it is, we won't be polling
	 * the register values, and won't create the related sysfs files.
	 */
	for (i = 0; i < 3; i++) {
		data->fan_ctrl[i] = f71805f_read8(data,
						  F71805F_REG_FAN_CTRL(i));
		/*
		 * Clear latch full bit, else "speed mode" fan speed control
		 * doesn't work
		 */
		if (data->fan_ctrl[i] & FAN_CTRL_LATCH_FULL) {
			data->fan_ctrl[i] &= ~FAN_CTRL_LATCH_FULL;
			f71805f_write8(data, F71805F_REG_FAN_CTRL(i),
				       data->fan_ctrl[i]);
		}
	}
}