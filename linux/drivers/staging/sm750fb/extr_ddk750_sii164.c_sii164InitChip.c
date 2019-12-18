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

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_I2C_SCL ; 
 int /*<<< orphan*/  DEFAULT_I2C_SDA ; 
 int /*<<< orphan*/  SII164_CONFIGURATION ; 
 unsigned char SII164_CONFIGURATION_BUS_12BITS ; 
 unsigned char SII164_CONFIGURATION_BUS_24BITS ; 
 unsigned char SII164_CONFIGURATION_CLOCK_DUAL ; 
 unsigned char SII164_CONFIGURATION_CLOCK_SINGLE ; 
 unsigned char SII164_CONFIGURATION_HSYNC_AS_IS ; 
 unsigned char SII164_CONFIGURATION_HSYNC_FORCE_LOW ; 
 unsigned char SII164_CONFIGURATION_LATCH_FALLING ; 
 unsigned char SII164_CONFIGURATION_LATCH_RISING ; 
 unsigned char SII164_CONFIGURATION_POWER_NORMAL ; 
 unsigned char SII164_CONFIGURATION_VSYNC_AS_IS ; 
 unsigned char SII164_CONFIGURATION_VSYNC_FORCE_LOW ; 
 int /*<<< orphan*/  SII164_DESKEW ; 
 unsigned char SII164_DESKEW_1_STEP ; 
 unsigned char SII164_DESKEW_2_STEP ; 
 unsigned char SII164_DESKEW_3_STEP ; 
 unsigned char SII164_DESKEW_4_STEP ; 
 unsigned char SII164_DESKEW_5_STEP ; 
 unsigned char SII164_DESKEW_6_STEP ; 
 unsigned char SII164_DESKEW_7_STEP ; 
 unsigned char SII164_DESKEW_8_STEP ; 
 unsigned char SII164_DESKEW_DISABLE ; 
 unsigned char SII164_DESKEW_ENABLE ; 
 scalar_t__ SII164_DEVICE_ID ; 
 int /*<<< orphan*/  SII164_I2C_ADDRESS ; 
 int /*<<< orphan*/  SII164_PLL ; 
 unsigned char SII164_PLL_FILTER_DISABLE ; 
 unsigned char SII164_PLL_FILTER_ENABLE ; 
 unsigned char SII164_PLL_FILTER_SYNC_CONTINUOUS_DISABLE ; 
 unsigned char SII164_PLL_FILTER_SYNC_CONTINUOUS_ENABLE ; 
 scalar_t__ SII164_VENDOR_ID ; 
 unsigned char i2cReadReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2cWriteReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 
 scalar_t__ sii164GetDeviceID () ; 
 scalar_t__ sii164GetVendorID () ; 
 int /*<<< orphan*/  sm750_hw_i2c_init (int) ; 
 int /*<<< orphan*/  sm750_sw_i2c_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

long sii164InitChip(unsigned char edge_select,
		    unsigned char bus_select,
		    unsigned char dual_edge_clk_select,
		    unsigned char hsync_enable,
		    unsigned char vsync_enable,
		    unsigned char deskew_enable,
		    unsigned char deskew_setting,
		    unsigned char continuous_sync_enable,
		    unsigned char pll_filter_enable,
		    unsigned char pll_filter_value)
{
	unsigned char config;

	/* Initialize the i2c bus */
#ifdef USE_HW_I2C
	/* Use fast mode. */
	sm750_hw_i2c_init(1);
#else
	sm750_sw_i2c_init(DEFAULT_I2C_SCL, DEFAULT_I2C_SDA);
#endif

	/* Check if SII164 Chip exists */
	if ((sii164GetVendorID() == SII164_VENDOR_ID) && (sii164GetDeviceID() == SII164_DEVICE_ID)) {
		/*
		 *  Initialize SII164 controller chip.
		 */

		/* Select the edge */
		if (edge_select == 0)
			config = SII164_CONFIGURATION_LATCH_FALLING;
		else
			config = SII164_CONFIGURATION_LATCH_RISING;

		/* Select bus wide */
		if (bus_select == 0)
			config |= SII164_CONFIGURATION_BUS_12BITS;
		else
			config |= SII164_CONFIGURATION_BUS_24BITS;

		/* Select Dual/Single Edge Clock */
		if (dual_edge_clk_select == 0)
			config |= SII164_CONFIGURATION_CLOCK_SINGLE;
		else
			config |= SII164_CONFIGURATION_CLOCK_DUAL;

		/* Select HSync Enable */
		if (hsync_enable == 0)
			config |= SII164_CONFIGURATION_HSYNC_FORCE_LOW;
		else
			config |= SII164_CONFIGURATION_HSYNC_AS_IS;

		/* Select VSync Enable */
		if (vsync_enable == 0)
			config |= SII164_CONFIGURATION_VSYNC_FORCE_LOW;
		else
			config |= SII164_CONFIGURATION_VSYNC_AS_IS;

		i2cWriteReg(SII164_I2C_ADDRESS, SII164_CONFIGURATION, config);

		/*
		 * De-skew enabled with default 111b value.
		 * This fixes some artifacts problem in some mode on board 2.2.
		 * Somehow this fix does not affect board 2.1.
		 */
		if (deskew_enable == 0)
			config = SII164_DESKEW_DISABLE;
		else
			config = SII164_DESKEW_ENABLE;

		switch (deskew_setting) {
		case 0:
			config |= SII164_DESKEW_1_STEP;
			break;
		case 1:
			config |= SII164_DESKEW_2_STEP;
			break;
		case 2:
			config |= SII164_DESKEW_3_STEP;
			break;
		case 3:
			config |= SII164_DESKEW_4_STEP;
			break;
		case 4:
			config |= SII164_DESKEW_5_STEP;
			break;
		case 5:
			config |= SII164_DESKEW_6_STEP;
			break;
		case 6:
			config |= SII164_DESKEW_7_STEP;
			break;
		case 7:
			config |= SII164_DESKEW_8_STEP;
			break;
		}
		i2cWriteReg(SII164_I2C_ADDRESS, SII164_DESKEW, config);

		/* Enable/Disable Continuous Sync. */
		if (continuous_sync_enable == 0)
			config = SII164_PLL_FILTER_SYNC_CONTINUOUS_DISABLE;
		else
			config = SII164_PLL_FILTER_SYNC_CONTINUOUS_ENABLE;

		/* Enable/Disable PLL Filter */
		if (pll_filter_enable == 0)
			config |= SII164_PLL_FILTER_DISABLE;
		else
			config |= SII164_PLL_FILTER_ENABLE;

		/* Set the PLL Filter value */
		config |= ((pll_filter_value & 0x07) << 1);

		i2cWriteReg(SII164_I2C_ADDRESS, SII164_PLL, config);

		/* Recover from Power Down and enable output. */
		config = i2cReadReg(SII164_I2C_ADDRESS, SII164_CONFIGURATION);
		config |= SII164_CONFIGURATION_POWER_NORMAL;
		i2cWriteReg(SII164_I2C_ADDRESS, SII164_CONFIGURATION, config);

		return 0;
	}

	/* Return -1 if initialization fails. */
	return -1;
}