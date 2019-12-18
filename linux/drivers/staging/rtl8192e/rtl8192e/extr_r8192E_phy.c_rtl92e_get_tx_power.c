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
struct r8192_priv {int /*<<< orphan*/  SifsTime; void* framesync; void* framesyncC34; void** DefaultInitialGain; void** MCSTxPowerLevelOriginalOffset; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*,...) ; 
 int /*<<< orphan*/  SIFS ; 
 int /*<<< orphan*/  rOFDM0_RxDetector2 ; 
 int /*<<< orphan*/  rOFDM0_RxDetector3 ; 
 int /*<<< orphan*/  rOFDM0_XAAGCCore1 ; 
 int /*<<< orphan*/  rOFDM0_XBAGCCore1 ; 
 int /*<<< orphan*/  rOFDM0_XCAGCCore1 ; 
 int /*<<< orphan*/  rOFDM0_XDAGCCore1 ; 
 int /*<<< orphan*/  rTxAGC_Mcs03_Mcs00 ; 
 int /*<<< orphan*/  rTxAGC_Mcs07_Mcs04 ; 
 int /*<<< orphan*/  rTxAGC_Mcs11_Mcs08 ; 
 int /*<<< orphan*/  rTxAGC_Mcs15_Mcs12 ; 
 int /*<<< orphan*/  rTxAGC_Rate18_06 ; 
 int /*<<< orphan*/  rTxAGC_Rate54_24 ; 
 void* rtl92e_readb (struct net_device*,int /*<<< orphan*/ ) ; 
 void* rtl92e_readl (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl92e_readw (struct net_device*,int /*<<< orphan*/ ) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

void rtl92e_get_tx_power(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);

	priv->MCSTxPowerLevelOriginalOffset[0] =
		rtl92e_readl(dev, rTxAGC_Rate18_06);
	priv->MCSTxPowerLevelOriginalOffset[1] =
		rtl92e_readl(dev, rTxAGC_Rate54_24);
	priv->MCSTxPowerLevelOriginalOffset[2] =
		rtl92e_readl(dev, rTxAGC_Mcs03_Mcs00);
	priv->MCSTxPowerLevelOriginalOffset[3] =
		rtl92e_readl(dev, rTxAGC_Mcs07_Mcs04);
	priv->MCSTxPowerLevelOriginalOffset[4] =
		rtl92e_readl(dev, rTxAGC_Mcs11_Mcs08);
	priv->MCSTxPowerLevelOriginalOffset[5] =
		rtl92e_readl(dev, rTxAGC_Mcs15_Mcs12);

	priv->DefaultInitialGain[0] = rtl92e_readb(dev, rOFDM0_XAAGCCore1);
	priv->DefaultInitialGain[1] = rtl92e_readb(dev, rOFDM0_XBAGCCore1);
	priv->DefaultInitialGain[2] = rtl92e_readb(dev, rOFDM0_XCAGCCore1);
	priv->DefaultInitialGain[3] = rtl92e_readb(dev, rOFDM0_XDAGCCore1);
	RT_TRACE(COMP_INIT,
		 "Default initial gain (c50=0x%x, c58=0x%x, c60=0x%x, c68=0x%x)\n",
		 priv->DefaultInitialGain[0], priv->DefaultInitialGain[1],
		 priv->DefaultInitialGain[2], priv->DefaultInitialGain[3]);

	priv->framesync = rtl92e_readb(dev, rOFDM0_RxDetector3);
	priv->framesyncC34 = rtl92e_readl(dev, rOFDM0_RxDetector2);
	RT_TRACE(COMP_INIT, "Default framesync (0x%x) = 0x%x\n",
		rOFDM0_RxDetector3, priv->framesync);
	priv->SifsTime = rtl92e_readw(dev, SIFS);
}