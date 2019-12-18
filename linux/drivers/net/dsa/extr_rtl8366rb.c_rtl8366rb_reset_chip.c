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
struct realtek_smi {int /*<<< orphan*/  dev; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int EIO ; 
 int RTL8366RB_CHIP_CTRL_RESET_HW ; 
 int /*<<< orphan*/  RTL8366RB_RESET_CTRL_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  realtek_smi_write_reg_noack (struct realtek_smi*,int /*<<< orphan*/ ,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int rtl8366rb_reset_chip(struct realtek_smi *smi)
{
	int timeout = 10;
	u32 val;
	int ret;

	realtek_smi_write_reg_noack(smi, RTL8366RB_RESET_CTRL_REG,
				    RTL8366RB_CHIP_CTRL_RESET_HW);
	do {
		usleep_range(20000, 25000);
		ret = regmap_read(smi->map, RTL8366RB_RESET_CTRL_REG, &val);
		if (ret)
			return ret;

		if (!(val & RTL8366RB_CHIP_CTRL_RESET_HW))
			break;
	} while (--timeout);

	if (!timeout) {
		dev_err(smi->dev, "timeout waiting for the switch to reset\n");
		return -EIO;
	}

	return 0;
}