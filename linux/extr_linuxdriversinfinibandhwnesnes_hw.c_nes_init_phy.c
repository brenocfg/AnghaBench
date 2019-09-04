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
typedef  size_t u32 ;
struct nes_device {size_t mac_index; struct nes_adapter* nesadapter; } ;
struct nes_adapter {int* phy_type; int* phy_index; int /*<<< orphan*/  phy_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  NES_IDX_MAC_TX_CONFIG ; 
#define  NES_PHY_TYPE_1G 131 
#define  NES_PHY_TYPE_ARGUS 130 
#define  NES_PHY_TYPE_KR 129 
#define  NES_PHY_TYPE_SFP_D 128 
 int nes_init_1g_phy (struct nes_device*,int,int) ; 
 int nes_init_2025_phy (struct nes_device*,int,int) ; 
 size_t nes_read_indexed (struct nes_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_write_indexed (struct nes_device*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int nes_init_phy(struct nes_device *nesdev)
{
	struct nes_adapter *nesadapter = nesdev->nesadapter;
	u32 mac_index = nesdev->mac_index;
	u32 tx_config = 0;
	unsigned long flags;
	u8  phy_type = nesadapter->phy_type[mac_index];
	u8  phy_index = nesadapter->phy_index[mac_index];
	int ret = 0;

	tx_config = nes_read_indexed(nesdev, NES_IDX_MAC_TX_CONFIG);
	if (phy_type == NES_PHY_TYPE_1G) {
		/* setup 1G MDIO operation */
		tx_config &= 0xFFFFFFE3;
		tx_config |= 0x04;
	} else {
		/* setup 10G MDIO operation */
		tx_config &= 0xFFFFFFE3;
		tx_config |= 0x1D;
	}
	nes_write_indexed(nesdev, NES_IDX_MAC_TX_CONFIG, tx_config);

	spin_lock_irqsave(&nesdev->nesadapter->phy_lock, flags);

	switch (phy_type) {
	case NES_PHY_TYPE_1G:
		ret = nes_init_1g_phy(nesdev, phy_type, phy_index);
		break;
	case NES_PHY_TYPE_ARGUS:
	case NES_PHY_TYPE_SFP_D:
	case NES_PHY_TYPE_KR:
		ret = nes_init_2025_phy(nesdev, phy_type, phy_index);
		break;
	}

	spin_unlock_irqrestore(&nesdev->nesadapter->phy_lock, flags);

	return ret;
}