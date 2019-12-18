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
struct axp20x_dev {int variant; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int AXP803_DCDC23_POLYPHASE_DUAL ; 
#define  AXP803_DCDC3 135 
 int AXP803_DCDC56_POLYPHASE_DUAL ; 
#define  AXP803_DCDC6 134 
#define  AXP803_ID 133 
 int /*<<< orphan*/  AXP803_POLYPHASE_CTRL ; 
 int AXP806_DCDCABC_POLYPHASE_MASK ; 
 int AXP806_DCDCABC_POLYPHASE_TRI ; 
 int AXP806_DCDCAB_POLYPHASE_DUAL ; 
#define  AXP806_DCDCB 132 
#define  AXP806_DCDCC 131 
 int AXP806_DCDCDE_POLYPHASE_DUAL ; 
#define  AXP806_DCDCE 130 
 int /*<<< orphan*/  AXP806_DCDC_MODE_CTRL2 ; 
#define  AXP806_ID 129 
#define  AXP813_ID 128 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool axp20x_is_polyphase_slave(struct axp20x_dev *axp20x, int id)
{
	u32 reg = 0;

	/*
	 * Currently in our supported AXP variants, only AXP803, AXP806,
	 * and AXP813 have polyphase regulators.
	 */
	switch (axp20x->variant) {
	case AXP803_ID:
	case AXP813_ID:
		regmap_read(axp20x->regmap, AXP803_POLYPHASE_CTRL, &reg);

		switch (id) {
		case AXP803_DCDC3:
			return !!(reg & AXP803_DCDC23_POLYPHASE_DUAL);
		case AXP803_DCDC6:
			return !!(reg & AXP803_DCDC56_POLYPHASE_DUAL);
		}
		break;

	case AXP806_ID:
		regmap_read(axp20x->regmap, AXP806_DCDC_MODE_CTRL2, &reg);

		switch (id) {
		case AXP806_DCDCB:
			return (((reg & AXP806_DCDCABC_POLYPHASE_MASK) ==
				AXP806_DCDCAB_POLYPHASE_DUAL) ||
				((reg & AXP806_DCDCABC_POLYPHASE_MASK) ==
				AXP806_DCDCABC_POLYPHASE_TRI));
		case AXP806_DCDCC:
			return ((reg & AXP806_DCDCABC_POLYPHASE_MASK) ==
				AXP806_DCDCABC_POLYPHASE_TRI);
		case AXP806_DCDCE:
			return !!(reg & AXP806_DCDCDE_POLYPHASE_DUAL);
		}
		break;

	default:
		return false;
	}

	return false;
}