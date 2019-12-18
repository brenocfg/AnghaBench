#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {int /*<<< orphan*/  rate; } ;
struct anx78xx {int* dpcd; int /*<<< orphan*/ * map; TYPE_1__ link; int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DOWNSPREAD_CTRL ; 
 int /*<<< orphan*/  DP_DPCD_REV ; 
#define  DP_LINK_BW_1_62 130 
#define  DP_LINK_BW_2_7 129 
#define  DP_LINK_BW_5_4 128 
 size_t DP_MAX_DOWNSPREAD ; 
 int DP_MAX_DOWNSPREAD_0_5 ; 
 int /*<<< orphan*/  DP_MAX_LINK_RATE ; 
 int /*<<< orphan*/  DP_RECEIVER_CAP_SIZE ; 
 int /*<<< orphan*/  DP_SPREAD_AMP_0_5 ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 
 size_t I2C_IDX_RX_P0 ; 
 size_t I2C_IDX_TX_P0 ; 
 size_t I2C_IDX_TX_P2 ; 
 int /*<<< orphan*/  SP_CH0_PD ; 
 scalar_t__ SP_DP_ANALOG_POWER_DOWN_REG ; 
 int /*<<< orphan*/  SP_DP_DOWNSPREAD_CTRL1_REG ; 
 int /*<<< orphan*/  SP_DP_LT_CTRL_REG ; 
 int /*<<< orphan*/  SP_DP_MAIN_LINK_BW_SET_REG ; 
 scalar_t__ SP_DP_SYSTEM_CTRL_BASE ; 
 int /*<<< orphan*/  SP_ENHANCED_MODE ; 
 int /*<<< orphan*/  SP_HDMI_MUTE_CTRL_REG ; 
 int SP_LT_EN ; 
 scalar_t__ SP_POWERDOWN_CTRL_REG ; 
 int /*<<< orphan*/  SP_TOTAL_PD ; 
 int /*<<< orphan*/  SP_VIDEO_EN ; 
 int /*<<< orphan*/  SP_VIDEO_MUTE ; 
 scalar_t__ SP_VID_CTRL1_REG ; 
 int anx78xx_clear_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int anx78xx_set_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int drm_dp_dpcd_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int**,int /*<<< orphan*/ ) ; 
 int drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int drm_dp_dpcd_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ drm_dp_enhanced_frame_cap (int*) ; 
 int drm_dp_link_configure (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int drm_dp_link_power_up (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int drm_dp_link_probe (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int drm_dp_link_rate_to_bw_code (int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int anx78xx_dp_link_training(struct anx78xx *anx78xx)
{
	u8 dp_bw, value;
	int err;

	err = regmap_write(anx78xx->map[I2C_IDX_RX_P0], SP_HDMI_MUTE_CTRL_REG,
			   0x0);
	if (err)
		return err;

	err = anx78xx_clear_bits(anx78xx->map[I2C_IDX_TX_P2],
				 SP_POWERDOWN_CTRL_REG,
				 SP_TOTAL_PD);
	if (err)
		return err;

	err = drm_dp_dpcd_readb(&anx78xx->aux, DP_MAX_LINK_RATE, &dp_bw);
	if (err < 0)
		return err;

	switch (dp_bw) {
	case DP_LINK_BW_1_62:
	case DP_LINK_BW_2_7:
	case DP_LINK_BW_5_4:
		break;

	default:
		DRM_DEBUG_KMS("DP bandwidth (%#02x) not supported\n", dp_bw);
		return -EINVAL;
	}

	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P2], SP_VID_CTRL1_REG,
			       SP_VIDEO_MUTE);
	if (err)
		return err;

	err = anx78xx_clear_bits(anx78xx->map[I2C_IDX_TX_P2],
				 SP_VID_CTRL1_REG, SP_VIDEO_EN);
	if (err)
		return err;

	/* Get DPCD info */
	err = drm_dp_dpcd_read(&anx78xx->aux, DP_DPCD_REV,
			       &anx78xx->dpcd, DP_RECEIVER_CAP_SIZE);
	if (err < 0) {
		DRM_ERROR("Failed to read DPCD: %d\n", err);
		return err;
	}

	/* Clear channel x SERDES power down */
	err = anx78xx_clear_bits(anx78xx->map[I2C_IDX_TX_P0],
				 SP_DP_ANALOG_POWER_DOWN_REG, SP_CH0_PD);
	if (err)
		return err;

	/* Check link capabilities */
	err = drm_dp_link_probe(&anx78xx->aux, &anx78xx->link);
	if (err < 0) {
		DRM_ERROR("Failed to probe link capabilities: %d\n", err);
		return err;
	}

	/* Power up the sink */
	err = drm_dp_link_power_up(&anx78xx->aux, &anx78xx->link);
	if (err < 0) {
		DRM_ERROR("Failed to power up DisplayPort link: %d\n", err);
		return err;
	}

	/* Possibly enable downspread on the sink */
	err = regmap_write(anx78xx->map[I2C_IDX_TX_P0],
			   SP_DP_DOWNSPREAD_CTRL1_REG, 0);
	if (err)
		return err;

	if (anx78xx->dpcd[DP_MAX_DOWNSPREAD] & DP_MAX_DOWNSPREAD_0_5) {
		DRM_DEBUG("Enable downspread on the sink\n");
		/* 4000PPM */
		err = regmap_write(anx78xx->map[I2C_IDX_TX_P0],
				   SP_DP_DOWNSPREAD_CTRL1_REG, 8);
		if (err)
			return err;

		err = drm_dp_dpcd_writeb(&anx78xx->aux, DP_DOWNSPREAD_CTRL,
					 DP_SPREAD_AMP_0_5);
		if (err < 0)
			return err;
	} else {
		err = drm_dp_dpcd_writeb(&anx78xx->aux, DP_DOWNSPREAD_CTRL, 0);
		if (err < 0)
			return err;
	}

	/* Set the lane count and the link rate on the sink */
	if (drm_dp_enhanced_frame_cap(anx78xx->dpcd))
		err = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P0],
				       SP_DP_SYSTEM_CTRL_BASE + 4,
				       SP_ENHANCED_MODE);
	else
		err = anx78xx_clear_bits(anx78xx->map[I2C_IDX_TX_P0],
					 SP_DP_SYSTEM_CTRL_BASE + 4,
					 SP_ENHANCED_MODE);
	if (err)
		return err;

	value = drm_dp_link_rate_to_bw_code(anx78xx->link.rate);
	err = regmap_write(anx78xx->map[I2C_IDX_TX_P0],
			   SP_DP_MAIN_LINK_BW_SET_REG, value);
	if (err)
		return err;

	err = drm_dp_link_configure(&anx78xx->aux, &anx78xx->link);
	if (err < 0) {
		DRM_ERROR("Failed to configure DisplayPort link: %d\n", err);
		return err;
	}

	/* Start training on the source */
	err = regmap_write(anx78xx->map[I2C_IDX_TX_P0], SP_DP_LT_CTRL_REG,
			   SP_LT_EN);
	if (err)
		return err;

	return 0;
}