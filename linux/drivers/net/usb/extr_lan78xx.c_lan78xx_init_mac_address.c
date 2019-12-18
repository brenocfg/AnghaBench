#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct lan78xx_net {TYPE_2__* net; TYPE_1__* udev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_MAC_OFFSET ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MAF_HI (int /*<<< orphan*/ ) ; 
 int MAF_HI_VALID_ ; 
 int /*<<< orphan*/  MAF_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RX_ADDRH ; 
 int /*<<< orphan*/  RX_ADDRL ; 
 int /*<<< orphan*/  eth_platform_get_mac_address (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  eth_random_addr (int*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ifup ; 
 scalar_t__ is_valid_ether_addr (int*) ; 
 scalar_t__ lan78xx_read_eeprom (struct lan78xx_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ lan78xx_read_otp (struct lan78xx_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int lan78xx_read_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int*) ; 
 int lan78xx_write_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_dbg (struct lan78xx_net*,int /*<<< orphan*/ ,TYPE_2__*,char*) ; 

__attribute__((used)) static void lan78xx_init_mac_address(struct lan78xx_net *dev)
{
	u32 addr_lo, addr_hi;
	int ret;
	u8 addr[6];

	ret = lan78xx_read_reg(dev, RX_ADDRL, &addr_lo);
	ret = lan78xx_read_reg(dev, RX_ADDRH, &addr_hi);

	addr[0] = addr_lo & 0xFF;
	addr[1] = (addr_lo >> 8) & 0xFF;
	addr[2] = (addr_lo >> 16) & 0xFF;
	addr[3] = (addr_lo >> 24) & 0xFF;
	addr[4] = addr_hi & 0xFF;
	addr[5] = (addr_hi >> 8) & 0xFF;

	if (!is_valid_ether_addr(addr)) {
		if (!eth_platform_get_mac_address(&dev->udev->dev, addr)) {
			/* valid address present in Device Tree */
			netif_dbg(dev, ifup, dev->net,
				  "MAC address read from Device Tree");
		} else if (((lan78xx_read_eeprom(dev, EEPROM_MAC_OFFSET,
						 ETH_ALEN, addr) == 0) ||
			    (lan78xx_read_otp(dev, EEPROM_MAC_OFFSET,
					      ETH_ALEN, addr) == 0)) &&
			   is_valid_ether_addr(addr)) {
			/* eeprom values are valid so use them */
			netif_dbg(dev, ifup, dev->net,
				  "MAC address read from EEPROM");
		} else {
			/* generate random MAC */
			eth_random_addr(addr);
			netif_dbg(dev, ifup, dev->net,
				  "MAC address set to random addr");
		}

		addr_lo = addr[0] | (addr[1] << 8) |
			  (addr[2] << 16) | (addr[3] << 24);
		addr_hi = addr[4] | (addr[5] << 8);

		ret = lan78xx_write_reg(dev, RX_ADDRL, addr_lo);
		ret = lan78xx_write_reg(dev, RX_ADDRH, addr_hi);
	}

	ret = lan78xx_write_reg(dev, MAF_LO(0), addr_lo);
	ret = lan78xx_write_reg(dev, MAF_HI(0), addr_hi | MAF_HI_VALID_);

	ether_addr_copy(dev->net->dev_addr, addr);
}