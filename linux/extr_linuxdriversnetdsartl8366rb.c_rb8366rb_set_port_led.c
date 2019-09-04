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
typedef  int u16 ;
struct realtek_smi {int /*<<< orphan*/  dev; int /*<<< orphan*/  map; scalar_t__ leds_disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTL8366RB_INTERRUPT_CONTROL_REG ; 
 int /*<<< orphan*/  RTL8366RB_LED_0_1_CTRL_REG ; 
 int RTL8366RB_LED_1_OFFSET ; 
 int /*<<< orphan*/  RTL8366RB_LED_2_3_CTRL_REG ; 
 int RTL8366RB_LED_3_OFFSET ; 
 int RTL8366RB_P4_RGMII_LED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rb8366rb_set_port_led(struct realtek_smi *smi,
				  int port, bool enable)
{
	u16 val = enable ? 0x3f : 0;
	int ret;

	if (smi->leds_disabled)
		return;

	switch (port) {
	case 0:
		ret = regmap_update_bits(smi->map,
					 RTL8366RB_LED_0_1_CTRL_REG,
					 0x3F, val);
		break;
	case 1:
		ret = regmap_update_bits(smi->map,
					 RTL8366RB_LED_0_1_CTRL_REG,
					 0x3F << RTL8366RB_LED_1_OFFSET,
					 val << RTL8366RB_LED_1_OFFSET);
		break;
	case 2:
		ret = regmap_update_bits(smi->map,
					 RTL8366RB_LED_2_3_CTRL_REG,
					 0x3F, val);
		break;
	case 3:
		ret = regmap_update_bits(smi->map,
					 RTL8366RB_LED_2_3_CTRL_REG,
					 0x3F << RTL8366RB_LED_3_OFFSET,
					 val << RTL8366RB_LED_3_OFFSET);
		break;
	case 4:
		ret = regmap_update_bits(smi->map,
					 RTL8366RB_INTERRUPT_CONTROL_REG,
					 RTL8366RB_P4_RGMII_LED,
					 enable ? RTL8366RB_P4_RGMII_LED : 0);
		break;
	default:
		dev_err(smi->dev, "no LED for port %d\n", port);
		return;
	}
	if (ret)
		dev_err(smi->dev, "error updating LED on port %d\n", port);
}