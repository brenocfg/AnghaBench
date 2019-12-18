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
struct net_device {int dummy; } ;
typedef  enum baseband_config_type { ____Placeholder_baseband_config_type } baseband_config_type ;

/* Variables and functions */
 int AGCTAB_ArrayLength ; 
 int BASEBAND_CONFIG_AGC_TAB ; 
 int BASEBAND_CONFIG_PHY_REG ; 
 int /*<<< orphan*/  COMP_DBG ; 
 int PHY_REG_1T2RArrayLength ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Rtl8192UsbAGCTAB_Array ; 
 int /*<<< orphan*/ * Rtl8192UsbPHY_REG_1T2RArray ; 
 int /*<<< orphan*/  bMaskDWord ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl8192_phyConfigBB(struct net_device *dev,
				enum baseband_config_type ConfigType)
{
	u32 i;

	if (ConfigType == BASEBAND_CONFIG_PHY_REG) {
		for (i = 0; i < PHY_REG_1T2RArrayLength; i += 2) {
			rtl8192_setBBreg(dev, Rtl8192UsbPHY_REG_1T2RArray[i],
					 bMaskDWord,
					 Rtl8192UsbPHY_REG_1T2RArray[i+1]);
			RT_TRACE(COMP_DBG,
				 "i: %x, Rtl819xUsbPHY_REGArray[0]=%x Rtl819xUsbPHY_REGArray[1]=%x\n",
				 i, Rtl8192UsbPHY_REG_1T2RArray[i],
				 Rtl8192UsbPHY_REG_1T2RArray[i+1]);
		}
	} else if (ConfigType == BASEBAND_CONFIG_AGC_TAB) {
		for (i = 0; i < AGCTAB_ArrayLength; i += 2) {
			rtl8192_setBBreg(dev, Rtl8192UsbAGCTAB_Array[i],
					 bMaskDWord, Rtl8192UsbAGCTAB_Array[i+1]);
			RT_TRACE(COMP_DBG,
				 "i: %x, Rtl8192UsbAGCTAB_Array[0]=%x Rtl8192UsbAGCTAB_Array[1]=%x\n",
				 i, Rtl8192UsbAGCTAB_Array[i],
				 Rtl8192UsbAGCTAB_Array[i+1]);
		}
	}
}