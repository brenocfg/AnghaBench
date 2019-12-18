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
typedef  int u16 ;
struct pch_gbe_hw {TYPE_1__* reg; } ;
struct pch_gbe_adapter {struct pch_gbe_hw hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  RGMII_CTRL; } ;

/* Variables and functions */
 unsigned long PCH_GBE_MAC_RGMII_CTRL_SETTING ; 
 unsigned long PCH_GBE_RGMII_RATE_125M ; 
 unsigned long PCH_GBE_RGMII_RATE_25M ; 
 unsigned long PCH_GBE_RGMII_RATE_2_5M ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int /*<<< orphan*/  iowrite32 (unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pch_gbe_set_rgmii_ctrl(struct pch_gbe_adapter *adapter, u16 speed,
				    u16 duplex)
{
	struct pch_gbe_hw *hw = &adapter->hw;
	unsigned long rgmii = 0;

	/* Set the RGMII control. */
	switch (speed) {
	case SPEED_10:
		rgmii = (PCH_GBE_RGMII_RATE_2_5M |
			 PCH_GBE_MAC_RGMII_CTRL_SETTING);
		break;
	case SPEED_100:
		rgmii = (PCH_GBE_RGMII_RATE_25M |
			 PCH_GBE_MAC_RGMII_CTRL_SETTING);
		break;
	case SPEED_1000:
		rgmii = (PCH_GBE_RGMII_RATE_125M |
			 PCH_GBE_MAC_RGMII_CTRL_SETTING);
		break;
	}
	iowrite32(rgmii, &hw->reg->RGMII_CTRL);
}