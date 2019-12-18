#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct mdp4_kms {int dummy; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int bpc; } ;
struct drm_connector {TYPE_1__ display_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int MDP4_LCDC_LVDS_INTF_CTL_CH1_CLK_LANE_EN ; 
 int MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE0_EN ; 
 int MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE1_EN ; 
 int MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE2_EN ; 
 int MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE3_EN ; 
 int MDP4_LCDC_LVDS_INTF_CTL_CH2_CLK_LANE_EN ; 
 int MDP4_LCDC_LVDS_INTF_CTL_CH2_DATA_LANE0_EN ; 
 int MDP4_LCDC_LVDS_INTF_CTL_CH2_DATA_LANE1_EN ; 
 int MDP4_LCDC_LVDS_INTF_CTL_CH2_DATA_LANE2_EN ; 
 int MDP4_LCDC_LVDS_INTF_CTL_CH2_DATA_LANE3_EN ; 
 int MDP4_LCDC_LVDS_INTF_CTL_CH_SWAP ; 
 int MDP4_LCDC_LVDS_INTF_CTL_ENABLE ; 
 int MDP4_LCDC_LVDS_INTF_CTL_MODE_SEL ; 
 int MDP4_LCDC_LVDS_INTF_CTL_RGB_OUT ; 
 int MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT0 (int) ; 
 int MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT1 (int) ; 
 int MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT2 (int) ; 
 int MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT3 (int) ; 
 int MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT4 (int) ; 
 int MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT5 (int) ; 
 int MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT6 (int) ; 
 int MDP4_LVDS_PHY_CFG0_CHANNEL0 ; 
 int MDP4_LVDS_PHY_CFG0_CHANNEL1 ; 
 int MDP4_LVDS_PHY_CFG0_SERIALIZATION_ENBLE ; 
 int /*<<< orphan*/  REG_MDP4_LCDC_LVDS_INTF_CTL ; 
 int /*<<< orphan*/  REG_MDP4_LCDC_LVDS_MUX_CTL_3_TO_0 (int) ; 
 int /*<<< orphan*/  REG_MDP4_LCDC_LVDS_MUX_CTL_6_TO_4 (int) ; 
 int /*<<< orphan*/  REG_MDP4_LVDS_PHY_CFG0 ; 
 int /*<<< orphan*/  REG_MDP4_LVDS_PHY_CFG2 ; 
 struct drm_connector* get_connector (struct drm_encoder*) ; 
 struct mdp4_kms* get_kms (struct drm_encoder*) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  mdp4_write (struct mdp4_kms*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void setup_phy(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	struct drm_connector *connector = get_connector(encoder);
	struct mdp4_kms *mdp4_kms = get_kms(encoder);
	uint32_t lvds_intf = 0, lvds_phy_cfg0 = 0;
	int bpp, nchan, swap;

	if (!connector)
		return;

	bpp = 3 * connector->display_info.bpc;

	if (!bpp)
		bpp = 18;

	/* TODO, these should come from panel somehow: */
	nchan = 1;
	swap = 0;

	switch (bpp) {
	case 24:
		mdp4_write(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_3_TO_0(0),
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT0(0x08) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT1(0x05) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT2(0x04) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT3(0x03));
		mdp4_write(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_6_TO_4(0),
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT4(0x02) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT5(0x01) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT6(0x00));
		mdp4_write(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_3_TO_0(1),
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT0(0x11) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT1(0x10) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT2(0x0d) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT3(0x0c));
		mdp4_write(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_6_TO_4(1),
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT4(0x0b) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT5(0x0a) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT6(0x09));
		mdp4_write(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_3_TO_0(2),
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT0(0x1a) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT1(0x19) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT2(0x18) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT3(0x15));
		mdp4_write(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_6_TO_4(2),
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT4(0x14) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT5(0x13) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT6(0x12));
		mdp4_write(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_3_TO_0(3),
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT0(0x1b) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT1(0x17) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT2(0x16) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT3(0x0f));
		mdp4_write(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_6_TO_4(3),
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT4(0x0e) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT5(0x07) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT6(0x06));
		if (nchan == 2) {
			lvds_intf |= MDP4_LCDC_LVDS_INTF_CTL_CH2_DATA_LANE3_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH2_DATA_LANE2_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH2_DATA_LANE1_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH2_DATA_LANE0_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE3_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE2_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE1_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE0_EN;
		} else {
			lvds_intf |= MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE3_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE2_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE1_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE0_EN;
		}
		break;

	case 18:
		mdp4_write(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_3_TO_0(0),
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT0(0x0a) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT1(0x07) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT2(0x06) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT3(0x05));
		mdp4_write(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_6_TO_4(0),
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT4(0x04) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT5(0x03) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT6(0x02));
		mdp4_write(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_3_TO_0(1),
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT0(0x13) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT1(0x12) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT2(0x0f) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT3(0x0e));
		mdp4_write(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_6_TO_4(1),
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT4(0x0d) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT5(0x0c) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT6(0x0b));
		mdp4_write(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_3_TO_0(2),
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT0(0x1a) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT1(0x19) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT2(0x18) |
				MDP4_LCDC_LVDS_MUX_CTL_3_TO_0_BIT3(0x17));
		mdp4_write(mdp4_kms, REG_MDP4_LCDC_LVDS_MUX_CTL_6_TO_4(2),
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT4(0x16) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT5(0x15) |
				MDP4_LCDC_LVDS_MUX_CTL_6_TO_4_BIT6(0x14));
		if (nchan == 2) {
			lvds_intf |= MDP4_LCDC_LVDS_INTF_CTL_CH2_DATA_LANE2_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH2_DATA_LANE1_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH2_DATA_LANE0_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE2_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE1_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE0_EN;
		} else {
			lvds_intf |= MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE2_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE1_EN |
					MDP4_LCDC_LVDS_INTF_CTL_CH1_DATA_LANE0_EN;
		}
		lvds_intf |= MDP4_LCDC_LVDS_INTF_CTL_RGB_OUT;
		break;

	default:
		DRM_DEV_ERROR(dev->dev, "unknown bpp: %d\n", bpp);
		return;
	}

	switch (nchan) {
	case 1:
		lvds_phy_cfg0 = MDP4_LVDS_PHY_CFG0_CHANNEL0;
		lvds_intf |= MDP4_LCDC_LVDS_INTF_CTL_CH1_CLK_LANE_EN |
				MDP4_LCDC_LVDS_INTF_CTL_MODE_SEL;
		break;
	case 2:
		lvds_phy_cfg0 = MDP4_LVDS_PHY_CFG0_CHANNEL0 |
				MDP4_LVDS_PHY_CFG0_CHANNEL1;
		lvds_intf |= MDP4_LCDC_LVDS_INTF_CTL_CH2_CLK_LANE_EN |
				MDP4_LCDC_LVDS_INTF_CTL_CH1_CLK_LANE_EN;
		break;
	default:
		DRM_DEV_ERROR(dev->dev, "unknown # of channels: %d\n", nchan);
		return;
	}

	if (swap)
		lvds_intf |= MDP4_LCDC_LVDS_INTF_CTL_CH_SWAP;

	lvds_intf |= MDP4_LCDC_LVDS_INTF_CTL_ENABLE;

	mdp4_write(mdp4_kms, REG_MDP4_LVDS_PHY_CFG0, lvds_phy_cfg0);
	mdp4_write(mdp4_kms, REG_MDP4_LCDC_LVDS_INTF_CTL, lvds_intf);
	mdp4_write(mdp4_kms, REG_MDP4_LVDS_PHY_CFG2, 0x30);

	mb();
	udelay(1);
	lvds_phy_cfg0 |= MDP4_LVDS_PHY_CFG0_SERIALIZATION_ENBLE;
	mdp4_write(mdp4_kms, REG_MDP4_LVDS_PHY_CFG0, lvds_phy_cfg0);
}