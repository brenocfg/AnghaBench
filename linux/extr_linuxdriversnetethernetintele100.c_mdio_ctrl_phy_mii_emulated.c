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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct nic {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int ADVERTISE_10FULL ; 
 int ADVERTISE_10HALF ; 
 int BMCR_ANENABLE ; 
 int BMCR_FULLDPLX ; 
 int BMSR_10FULL ; 
 int BMSR_ANEGCAPABLE ; 
 int BMSR_LSTATUS ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
#define  MII_ADVERTISE 130 
#define  MII_BMCR 129 
#define  MII_BMSR 128 
 int /*<<< orphan*/  hw ; 
 scalar_t__ mdi_read ; 
 int /*<<< orphan*/  netif_printk (struct nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static u16 mdio_ctrl_phy_mii_emulated(struct nic *nic,
				      u32 addr,
				      u32 dir,
				      u32 reg,
				      u16 data)
{
	/* might need to allocate a netdev_priv'ed register array eventually
	 * to be able to record state changes, but for now
	 * some fully hardcoded register handling ought to be ok I guess. */

	if (dir == mdi_read) {
		switch (reg) {
		case MII_BMCR:
			/* Auto-negotiation, right? */
			return  BMCR_ANENABLE |
				BMCR_FULLDPLX;
		case MII_BMSR:
			return	BMSR_LSTATUS /* for mii_link_ok() */ |
				BMSR_ANEGCAPABLE |
				BMSR_10FULL;
		case MII_ADVERTISE:
			/* 80c24 is a "combo card" PHY, right? */
			return	ADVERTISE_10HALF |
				ADVERTISE_10FULL;
		default:
			netif_printk(nic, hw, KERN_DEBUG, nic->netdev,
				     "%s:addr=%d, reg=%d, data=0x%04X: unimplemented emulation!\n",
				     dir == mdi_read ? "READ" : "WRITE",
				     addr, reg, data);
			return 0xFFFF;
		}
	} else {
		switch (reg) {
		default:
			netif_printk(nic, hw, KERN_DEBUG, nic->netdev,
				     "%s:addr=%d, reg=%d, data=0x%04X: unimplemented emulation!\n",
				     dir == mdi_read ? "READ" : "WRITE",
				     addr, reg, data);
			return 0xFFFF;
		}
	}
}