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
struct fusb302_chip {size_t src_current_status; } ;
typedef  enum typec_cc_status { ____Placeholder_typec_cc_status } typec_cc_status ;
typedef  enum typec_cc_polarity { ____Placeholder_typec_cc_polarity } typec_cc_polarity ;

/* Variables and functions */
 int /*<<< orphan*/  FUSB_REG_MEASURE ; 
 int /*<<< orphan*/  FUSB_REG_STATUS0 ; 
 int FUSB_REG_STATUS0_COMP ; 
 int /*<<< orphan*/  FUSB_REG_SWITCHES0 ; 
 int FUSB_REG_SWITCHES0_CC1_PU_EN ; 
 int FUSB_REG_SWITCHES0_CC2_PU_EN ; 
 int FUSB_REG_SWITCHES0_MEAS_CC1 ; 
 int FUSB_REG_SWITCHES0_MEAS_CC2 ; 
 int TYPEC_CC_OPEN ; 
 int TYPEC_CC_RA ; 
 int TYPEC_CC_RD ; 
 int TYPEC_POLARITY_CC1 ; 
 int fusb302_i2c_read (struct fusb302_chip*,int /*<<< orphan*/ ,int*) ; 
 int fusb302_i2c_write (struct fusb302_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fusb302_log (struct fusb302_chip*,char*,int) ; 
 int* ra_mda_value ; 
 int* rd_mda_value ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int fusb302_get_src_cc_status(struct fusb302_chip *chip,
				     enum typec_cc_polarity cc_polarity,
				     enum typec_cc_status *cc)
{
	u8 ra_mda = ra_mda_value[chip->src_current_status];
	u8 rd_mda = rd_mda_value[chip->src_current_status];
	u8 switches0_data, status0;
	int ret;

	/* Step 1: Set switches so that we measure the right CC pin */
	switches0_data = (cc_polarity == TYPEC_POLARITY_CC1) ?
		FUSB_REG_SWITCHES0_CC1_PU_EN | FUSB_REG_SWITCHES0_MEAS_CC1 :
		FUSB_REG_SWITCHES0_CC2_PU_EN | FUSB_REG_SWITCHES0_MEAS_CC2;
	ret = fusb302_i2c_write(chip, FUSB_REG_SWITCHES0, switches0_data);
	if (ret < 0)
		return ret;

	fusb302_i2c_read(chip, FUSB_REG_SWITCHES0, &status0);
	fusb302_log(chip, "get_src_cc_status switches: 0x%0x", status0);

	/* Step 2: Set compararator volt to differentiate between Open and Rd */
	ret = fusb302_i2c_write(chip, FUSB_REG_MEASURE, rd_mda);
	if (ret < 0)
		return ret;

	usleep_range(50, 100);
	ret = fusb302_i2c_read(chip, FUSB_REG_STATUS0, &status0);
	if (ret < 0)
		return ret;

	fusb302_log(chip, "get_src_cc_status rd_mda status0: 0x%0x", status0);
	if (status0 & FUSB_REG_STATUS0_COMP) {
		*cc = TYPEC_CC_OPEN;
		return 0;
	}

	/* Step 3: Set compararator input to differentiate between Rd and Ra. */
	ret = fusb302_i2c_write(chip, FUSB_REG_MEASURE, ra_mda);
	if (ret < 0)
		return ret;

	usleep_range(50, 100);
	ret = fusb302_i2c_read(chip, FUSB_REG_STATUS0, &status0);
	if (ret < 0)
		return ret;

	fusb302_log(chip, "get_src_cc_status ra_mda status0: 0x%0x", status0);
	if (status0 & FUSB_REG_STATUS0_COMP)
		*cc = TYPEC_CC_RD;
	else
		*cc = TYPEC_CC_RA;

	return 0;
}