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
struct max8997_muic_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  edev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL1_SW_AUDIO ; 
 int EINVAL ; 
 int /*<<< orphan*/  EXTCON_DOCK ; 
#define  MAX8997_MUIC_ADC_AV_CABLE_NOLOAD 129 
#define  MAX8997_MUIC_ADC_FACTORY_MODE_UART_ON 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  extcon_set_state_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int max8997_muic_set_path (struct max8997_muic_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max8997_muic_handle_dock(struct max8997_muic_info *info,
			int cable_type, bool attached)
{
	int ret = 0;

	ret = max8997_muic_set_path(info, CONTROL1_SW_AUDIO, attached);
	if (ret) {
		dev_err(info->dev, "failed to update muic register\n");
		return ret;
	}

	switch (cable_type) {
	case MAX8997_MUIC_ADC_AV_CABLE_NOLOAD:
	case MAX8997_MUIC_ADC_FACTORY_MODE_UART_ON:
		extcon_set_state_sync(info->edev, EXTCON_DOCK, attached);
		break;
	default:
		dev_err(info->dev, "failed to detect %s dock device\n",
			attached ? "attached" : "detached");
		return -EINVAL;
	}

	return 0;
}