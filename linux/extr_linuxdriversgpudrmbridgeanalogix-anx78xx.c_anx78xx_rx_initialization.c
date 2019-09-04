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
struct anx78xx {int /*<<< orphan*/ * map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int BIT (int) ; 
 size_t I2C_IDX_RX_P0 ; 
 size_t I2C_IDX_TX_P0 ; 
 int SP_AAC_EN ; 
 int SP_AAC_OE ; 
 int SP_AEC_EN21 ; 
 scalar_t__ SP_AUDVID_CTRL_REG ; 
 scalar_t__ SP_AUD_EXCEPTION_ENABLE_BASE ; 
 int SP_AUD_MUTE ; 
 int SP_AVC_EN ; 
 scalar_t__ SP_CHIP_CTRL_REG ; 
 int SP_DIGITAL_CKDT_EN ; 
 int /*<<< orphan*/  SP_DP_EXTRA_I2C_DEV_ADDR_REG ; 
 int SP_HDCP_MAN_RST ; 
 int /*<<< orphan*/  SP_HDMI_MUTE_CTRL_REG ; 
 int SP_I2C_EXTRA_ADDR ; 
 int SP_MAN_HDMI5V_DET ; 
 int SP_PLLLOCK_CKDT_EN ; 
 int SP_PWDN_CTRL ; 
 int SP_R2Y_INPUT_LIMIT ; 
 scalar_t__ SP_SOFTWARE_RESET1_REG ; 
 int SP_SW_MAN_RST ; 
 scalar_t__ SP_SYSTEM_POWER_DOWN1_REG ; 
 int SP_TMDS_RST ; 
 int SP_VIDEO_RST ; 
 scalar_t__ SP_VID_DATA_RANGE_CTRL_REG ; 
 int SP_VID_MUTE ; 
 int anx78xx_clear_bits (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int anx78xx_clear_hpd (struct anx78xx*) ; 
 int anx78xx_set_bits (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int regmap_multi_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tmds_phy_initialization ; 

__attribute__((used)) static int anx78xx_rx_initialization(struct anx78xx *anx78xx)
{
	int err;

	err = regmap_write(anx78xx->map[I2C_IDX_RX_P0], SP_HDMI_MUTE_CTRL_REG,
			   SP_AUD_MUTE | SP_VID_MUTE);
	if (err)
		return err;

	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_RX_P0], SP_CHIP_CTRL_REG,
			       SP_MAN_HDMI5V_DET | SP_PLLLOCK_CKDT_EN |
			       SP_DIGITAL_CKDT_EN);
	if (err)
		return err;

	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_RX_P0],
			       SP_SOFTWARE_RESET1_REG, SP_HDCP_MAN_RST |
			       SP_SW_MAN_RST | SP_TMDS_RST | SP_VIDEO_RST);
	if (err)
		return err;

	err = anx78xx_clear_bits(anx78xx->map[I2C_IDX_RX_P0],
				 SP_SOFTWARE_RESET1_REG, SP_HDCP_MAN_RST |
				 SP_SW_MAN_RST | SP_TMDS_RST | SP_VIDEO_RST);
	if (err)
		return err;

	/* Sync detect change, GP set mute */
	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_RX_P0],
			       SP_AUD_EXCEPTION_ENABLE_BASE + 1, BIT(5) |
			       BIT(6));
	if (err)
		return err;

	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_RX_P0],
			       SP_AUD_EXCEPTION_ENABLE_BASE + 3,
			       SP_AEC_EN21);
	if (err)
		return err;

	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_RX_P0], SP_AUDVID_CTRL_REG,
			       SP_AVC_EN | SP_AAC_OE | SP_AAC_EN);
	if (err)
		return err;

	err = anx78xx_clear_bits(anx78xx->map[I2C_IDX_RX_P0],
				 SP_SYSTEM_POWER_DOWN1_REG, SP_PWDN_CTRL);
	if (err)
		return err;

	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_RX_P0],
			       SP_VID_DATA_RANGE_CTRL_REG, SP_R2Y_INPUT_LIMIT);
	if (err)
		return err;

	/* Enable DDC stretch */
	err = regmap_write(anx78xx->map[I2C_IDX_TX_P0],
			   SP_DP_EXTRA_I2C_DEV_ADDR_REG, SP_I2C_EXTRA_ADDR);
	if (err)
		return err;

	/* TMDS phy initialization */
	err = regmap_multi_reg_write(anx78xx->map[I2C_IDX_RX_P0],
				     tmds_phy_initialization,
				     ARRAY_SIZE(tmds_phy_initialization));
	if (err)
		return err;

	err = anx78xx_clear_hpd(anx78xx);
	if (err)
		return err;

	return 0;
}