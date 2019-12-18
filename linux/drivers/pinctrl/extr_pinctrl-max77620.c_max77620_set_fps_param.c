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
struct max77620_pctrl_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  rmap; struct max77620_fps_config* fps_config; } ;
struct max77620_fps_config {int active_fps_src; int suspend_fps_src; int active_power_up_slots; int suspend_power_up_slots; int active_power_down_slots; int suspend_power_down_slots; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MAX77620_ACTIVE_FPS_POWER_DOWN_SLOTS 133 
#define  MAX77620_ACTIVE_FPS_POWER_ON_SLOTS 132 
#define  MAX77620_ACTIVE_FPS_SOURCE 131 
 int MAX77620_FPS_PD_PERIOD_MASK ; 
 int MAX77620_FPS_PD_PERIOD_SHIFT ; 
 int MAX77620_FPS_PU_PERIOD_MASK ; 
 int MAX77620_FPS_PU_PERIOD_SHIFT ; 
 int MAX77620_FPS_SRC_MASK ; 
 int MAX77620_FPS_SRC_SHIFT ; 
 int MAX77620_GPIO1 ; 
 int MAX77620_GPIO3 ; 
 int MAX77620_REG_FPS_GPIO1 ; 
#define  MAX77620_SUSPEND_FPS_POWER_DOWN_SLOTS 130 
#define  MAX77620_SUSPEND_FPS_POWER_ON_SLOTS 129 
#define  MAX77620_SUSPEND_FPS_SOURCE 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int max77620_set_fps_param(struct max77620_pctrl_info *mpci,
				  int pin, int param)
{
	struct max77620_fps_config *fps_config = &mpci->fps_config[pin];
	int addr, ret;
	int param_val;
	int mask, shift;

	if ((pin < MAX77620_GPIO1) || (pin > MAX77620_GPIO3))
		return 0;

	addr = MAX77620_REG_FPS_GPIO1 + pin - 1;
	switch (param) {
	case MAX77620_ACTIVE_FPS_SOURCE:
	case MAX77620_SUSPEND_FPS_SOURCE:
		mask = MAX77620_FPS_SRC_MASK;
		shift = MAX77620_FPS_SRC_SHIFT;
		param_val = fps_config->active_fps_src;
		if (param == MAX77620_SUSPEND_FPS_SOURCE)
			param_val = fps_config->suspend_fps_src;
		break;

	case MAX77620_ACTIVE_FPS_POWER_ON_SLOTS:
	case MAX77620_SUSPEND_FPS_POWER_ON_SLOTS:
		mask = MAX77620_FPS_PU_PERIOD_MASK;
		shift = MAX77620_FPS_PU_PERIOD_SHIFT;
		param_val = fps_config->active_power_up_slots;
		if (param == MAX77620_SUSPEND_FPS_POWER_ON_SLOTS)
			param_val = fps_config->suspend_power_up_slots;
		break;

	case MAX77620_ACTIVE_FPS_POWER_DOWN_SLOTS:
	case MAX77620_SUSPEND_FPS_POWER_DOWN_SLOTS:
		mask = MAX77620_FPS_PD_PERIOD_MASK;
		shift = MAX77620_FPS_PD_PERIOD_SHIFT;
		param_val = fps_config->active_power_down_slots;
		if (param == MAX77620_SUSPEND_FPS_POWER_DOWN_SLOTS)
			param_val = fps_config->suspend_power_down_slots;
		break;

	default:
		dev_err(mpci->dev, "Invalid parameter %d for pin %d\n",
			param, pin);
		return -EINVAL;
	}

	if (param_val < 0)
		return 0;

	ret = regmap_update_bits(mpci->rmap, addr, mask, param_val << shift);
	if (ret < 0)
		dev_err(mpci->dev, "Reg 0x%02x update failed %d\n", addr, ret);

	return ret;
}