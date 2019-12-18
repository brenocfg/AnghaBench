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
struct fusb302_chip {int cc_polarity; scalar_t__ vconn_on; } ;
typedef  enum typec_cc_polarity { ____Placeholder_typec_cc_polarity } typec_cc_polarity ;

/* Variables and functions */
 int /*<<< orphan*/  FUSB_REG_SWITCHES0 ; 
 int FUSB_REG_SWITCHES0_CC1_PD_EN ; 
 int FUSB_REG_SWITCHES0_CC1_PU_EN ; 
 int FUSB_REG_SWITCHES0_CC2_PD_EN ; 
 int FUSB_REG_SWITCHES0_CC2_PU_EN ; 
 int FUSB_REG_SWITCHES0_MEAS_CC1 ; 
 int FUSB_REG_SWITCHES0_MEAS_CC2 ; 
 int FUSB_REG_SWITCHES0_VCONN_CC1 ; 
 int FUSB_REG_SWITCHES0_VCONN_CC2 ; 
 int /*<<< orphan*/  FUSB_REG_SWITCHES1 ; 
 int FUSB_REG_SWITCHES1_TXCC1_EN ; 
 int FUSB_REG_SWITCHES1_TXCC2_EN ; 
 int TYPEC_POLARITY_CC1 ; 
 int fusb302_i2c_mask_write (struct fusb302_chip*,int /*<<< orphan*/ ,int,int) ; 
 int fusb302_i2c_write (struct fusb302_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fusb302_set_cc_polarity_and_pull(struct fusb302_chip *chip,
					    enum typec_cc_polarity cc_polarity,
					    bool pull_up, bool pull_down)
{
	int ret = 0;
	u8 switches0_data = 0x00;
	u8 switches1_mask = FUSB_REG_SWITCHES1_TXCC1_EN |
			    FUSB_REG_SWITCHES1_TXCC2_EN;
	u8 switches1_data = 0x00;

	if (pull_down)
		switches0_data |= FUSB_REG_SWITCHES0_CC1_PD_EN |
				  FUSB_REG_SWITCHES0_CC2_PD_EN;

	if (cc_polarity == TYPEC_POLARITY_CC1) {
		switches0_data |= FUSB_REG_SWITCHES0_MEAS_CC1;
		if (chip->vconn_on)
			switches0_data |= FUSB_REG_SWITCHES0_VCONN_CC2;
		if (pull_up)
			switches0_data |= FUSB_REG_SWITCHES0_CC1_PU_EN;
		switches1_data = FUSB_REG_SWITCHES1_TXCC1_EN;
	} else {
		switches0_data |= FUSB_REG_SWITCHES0_MEAS_CC2;
		if (chip->vconn_on)
			switches0_data |= FUSB_REG_SWITCHES0_VCONN_CC1;
		if (pull_up)
			switches0_data |= FUSB_REG_SWITCHES0_CC2_PU_EN;
		switches1_data = FUSB_REG_SWITCHES1_TXCC2_EN;
	}
	ret = fusb302_i2c_write(chip, FUSB_REG_SWITCHES0, switches0_data);
	if (ret < 0)
		return ret;
	ret = fusb302_i2c_mask_write(chip, FUSB_REG_SWITCHES1,
				     switches1_mask, switches1_data);
	if (ret < 0)
		return ret;
	chip->cc_polarity = cc_polarity;

	return ret;
}