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
typedef  scalar_t__ u8 ;
struct r8192_priv {int chan; int /*<<< orphan*/  card_8192_version; } ;
struct net_device {int dummy; } ;
typedef  enum rf90_radio_path_e { ____Placeholder_rf90_radio_path_e } rf90_radio_path_e ;
typedef  enum ht_channel_width { ____Placeholder_ht_channel_width } ht_channel_width ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_ERR ; 
#define  HT_CHANNEL_WIDTH_20 129 
#define  HT_CHANNEL_WIDTH_20_40 128 
 scalar_t__ RF90_PATH_MAX ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  VERSION_819XU_A ; 
 int /*<<< orphan*/  VERSION_819XU_B ; 
 int /*<<< orphan*/  bMask12Bits ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_phy_CheckIsLegalRFPath (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  rtl8192_phy_SetRFReg (struct net_device*,int,int,int /*<<< orphan*/ ,int) ; 

void phy_set_rf8256_bandwidth(struct net_device *dev, enum ht_channel_width Bandwidth)
{
	u8	eRFPath;
	struct r8192_priv *priv = ieee80211_priv(dev);

	/* for(eRFPath = RF90_PATH_A; eRFPath <pHalData->NumTotalRFPath;
	 *  eRFPath++)
	 */
	for (eRFPath = 0; eRFPath < RF90_PATH_MAX; eRFPath++) {
		if (!rtl8192_phy_CheckIsLegalRFPath(dev, eRFPath))
			continue;

		switch (Bandwidth) {
		case HT_CHANNEL_WIDTH_20:
				if (priv->card_8192_version == VERSION_819XU_A ||
					priv->card_8192_version ==
					VERSION_819XU_B) { /* 8256 D-cut, E-cut, xiong: consider it later! */
					rtl8192_phy_SetRFReg(dev,
						(enum rf90_radio_path_e)eRFPath,
						0x0b, bMask12Bits, 0x100); /* phy para:1ba */
					rtl8192_phy_SetRFReg(dev,
						(enum rf90_radio_path_e)eRFPath,
						0x2c, bMask12Bits, 0x3d7);
					rtl8192_phy_SetRFReg(dev,
						(enum rf90_radio_path_e)eRFPath,
						0x0e, bMask12Bits, 0x021);
					rtl8192_phy_SetRFReg(dev,
						(enum rf90_radio_path_e)eRFPath,
						0x14, bMask12Bits, 0x5ab);
				} else {
					RT_TRACE(COMP_ERR, "phy_set_rf8256_bandwidth(): unknown hardware version\n");
					}
				break;
		case HT_CHANNEL_WIDTH_20_40:
				if (priv->card_8192_version == VERSION_819XU_A || priv->card_8192_version == VERSION_819XU_B) { /* 8256 D-cut, E-cut, xiong: consider it later! */
					rtl8192_phy_SetRFReg(dev, (enum rf90_radio_path_e)eRFPath, 0x0b, bMask12Bits, 0x300); /* phy para:3ba */
					rtl8192_phy_SetRFReg(dev, (enum rf90_radio_path_e)eRFPath, 0x2c, bMask12Bits, 0x3df);
					rtl8192_phy_SetRFReg(dev, (enum rf90_radio_path_e)eRFPath, 0x0e, bMask12Bits, 0x0a1);

					if (priv->chan == 3 || priv->chan == 9)
						/* I need to set priv->chan whenever current channel changes */
						rtl8192_phy_SetRFReg(dev, (enum rf90_radio_path_e)eRFPath, 0x14, bMask12Bits, 0x59b);
					else
						rtl8192_phy_SetRFReg(dev, (enum rf90_radio_path_e)eRFPath, 0x14, bMask12Bits, 0x5ab);
				} else {
					RT_TRACE(COMP_ERR, "phy_set_rf8256_bandwidth(): unknown hardware version\n");
					}
				break;
		default:
				RT_TRACE(COMP_ERR, "phy_set_rf8256_bandwidth(): unknown Bandwidth: %#X\n", Bandwidth);
				break;
		}
	}
}