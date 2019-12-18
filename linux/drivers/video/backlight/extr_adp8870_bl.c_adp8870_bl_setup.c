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
struct i2c_client {int dummy; } ;
struct backlight_device {int dummy; } ;
struct adp8870_bl {int cached_daylight_max; scalar_t__ revid; struct adp8870_backlight_platform_data* pdata; struct i2c_client* client; } ;
struct adp8870_backlight_platform_data {int bl_led_assign; int pwm_assign; int l1_daylight_max; int l1_daylight_dim; int l2_bright_max; int l2_bright_dim; int l3_office_max; int l3_office_dim; int l4_indoor_max; int l4_indor_dim; int l5_dark_max; int l5_dark_dim; int l2_trip; int l2_hyst; int l3_trip; int l3_hyst; int l4_trip; int l4_hyst; int l5_trip; int l5_hyst; int /*<<< orphan*/  bl_fade_out; int /*<<< orphan*/  bl_fade_in; int /*<<< orphan*/  bl_fade_law; int /*<<< orphan*/  abml_filt; scalar_t__ en_ambl_sens; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADP8870_ALS1_EN ; 
 int /*<<< orphan*/  ADP8870_BLDM1 ; 
 int /*<<< orphan*/  ADP8870_BLDM2 ; 
 int /*<<< orphan*/  ADP8870_BLDM3 ; 
 int /*<<< orphan*/  ADP8870_BLDM4 ; 
 int /*<<< orphan*/  ADP8870_BLDM5 ; 
 int /*<<< orphan*/  ADP8870_BLFR ; 
 int /*<<< orphan*/  ADP8870_BLMX1 ; 
 int /*<<< orphan*/  ADP8870_BLMX2 ; 
 int /*<<< orphan*/  ADP8870_BLMX3 ; 
 int /*<<< orphan*/  ADP8870_BLMX4 ; 
 int /*<<< orphan*/  ADP8870_BLMX5 ; 
 int /*<<< orphan*/  ADP8870_BLSEL ; 
 int /*<<< orphan*/  ADP8870_CFGR ; 
 int /*<<< orphan*/  ADP8870_CMP_CTL ; 
 int /*<<< orphan*/  ADP8870_L2HYS ; 
 int /*<<< orphan*/  ADP8870_L2TRP ; 
 int /*<<< orphan*/  ADP8870_L3HYS ; 
 int /*<<< orphan*/  ADP8870_L3TRP ; 
 int /*<<< orphan*/  ADP8870_L4HYS ; 
 int /*<<< orphan*/  ADP8870_L4TRP ; 
 int /*<<< orphan*/  ADP8870_L5HYS ; 
 int /*<<< orphan*/  ADP8870_L5TRP ; 
 int /*<<< orphan*/  ADP8870_MDCR ; 
 int /*<<< orphan*/  ADP8870_PWMLED ; 
 int ALS_CMPR_CFG_VAL (int /*<<< orphan*/ ) ; 
 int BLEN ; 
 int BL_CFGR_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DIM_EN ; 
 int FADE_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GDWN_DIS ; 
 int L2_EN ; 
 int L3_EN ; 
 int L4_EN ; 
 int L5_EN ; 
 int NSTBY ; 
 int adp8870_set_bits (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int adp8870_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct adp8870_bl* bl_get_data (struct backlight_device*) ; 

__attribute__((used)) static int adp8870_bl_setup(struct backlight_device *bl)
{
	struct adp8870_bl *data = bl_get_data(bl);
	struct i2c_client *client = data->client;
	struct adp8870_backlight_platform_data *pdata = data->pdata;
	int ret = 0;

	ret = adp8870_write(client, ADP8870_BLSEL, ~pdata->bl_led_assign);
	if (ret)
		return ret;

	ret = adp8870_write(client, ADP8870_PWMLED, pdata->pwm_assign);
	if (ret)
		return ret;

	ret = adp8870_write(client, ADP8870_BLMX1, pdata->l1_daylight_max);
	if (ret)
		return ret;

	ret = adp8870_write(client, ADP8870_BLDM1, pdata->l1_daylight_dim);
	if (ret)
		return ret;

	if (pdata->en_ambl_sens) {
		data->cached_daylight_max = pdata->l1_daylight_max;
		ret = adp8870_write(client, ADP8870_BLMX2,
						pdata->l2_bright_max);
		if (ret)
			return ret;
		ret = adp8870_write(client, ADP8870_BLDM2,
						pdata->l2_bright_dim);
		if (ret)
			return ret;

		ret = adp8870_write(client, ADP8870_BLMX3,
						pdata->l3_office_max);
		if (ret)
			return ret;
		ret = adp8870_write(client, ADP8870_BLDM3,
						pdata->l3_office_dim);
		if (ret)
			return ret;

		ret = adp8870_write(client, ADP8870_BLMX4,
						pdata->l4_indoor_max);
		if (ret)
			return ret;

		ret = adp8870_write(client, ADP8870_BLDM4,
						pdata->l4_indor_dim);
		if (ret)
			return ret;

		ret = adp8870_write(client, ADP8870_BLMX5,
						pdata->l5_dark_max);
		if (ret)
			return ret;

		ret = adp8870_write(client, ADP8870_BLDM5,
						pdata->l5_dark_dim);
		if (ret)
			return ret;

		ret = adp8870_write(client, ADP8870_L2TRP, pdata->l2_trip);
		if (ret)
			return ret;

		ret = adp8870_write(client, ADP8870_L2HYS, pdata->l2_hyst);
		if (ret)
			return ret;

		ret = adp8870_write(client, ADP8870_L3TRP, pdata->l3_trip);
		if (ret)
			return ret;

		ret = adp8870_write(client, ADP8870_L3HYS, pdata->l3_hyst);
		if (ret)
			return ret;

		ret = adp8870_write(client, ADP8870_L4TRP, pdata->l4_trip);
		if (ret)
			return ret;

		ret = adp8870_write(client, ADP8870_L4HYS, pdata->l4_hyst);
		if (ret)
			return ret;

		ret = adp8870_write(client, ADP8870_L5TRP, pdata->l5_trip);
		if (ret)
			return ret;

		ret = adp8870_write(client, ADP8870_L5HYS, pdata->l5_hyst);
		if (ret)
			return ret;

		ret = adp8870_write(client, ADP8870_ALS1_EN, L5_EN | L4_EN |
						L3_EN | L2_EN);
		if (ret)
			return ret;

		ret = adp8870_write(client, ADP8870_CMP_CTL,
			ALS_CMPR_CFG_VAL(pdata->abml_filt));
		if (ret)
			return ret;
	}

	ret = adp8870_write(client, ADP8870_CFGR,
			BL_CFGR_VAL(pdata->bl_fade_law, 0));
	if (ret)
		return ret;

	ret = adp8870_write(client, ADP8870_BLFR, FADE_VAL(pdata->bl_fade_in,
			pdata->bl_fade_out));
	if (ret)
		return ret;
	/*
	 * ADP8870 Rev0 requires GDWN_DIS bit set
	 */

	ret = adp8870_set_bits(client, ADP8870_MDCR, BLEN | DIM_EN | NSTBY |
			(data->revid == 0 ? GDWN_DIS : 0));

	return ret;
}