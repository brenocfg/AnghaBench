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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct dnet {TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  addr ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DNET_INTERNAL_MAC_ADDR_0_REG ; 
 int /*<<< orphan*/  DNET_INTERNAL_MAC_ADDR_1_REG ; 
 int /*<<< orphan*/  DNET_INTERNAL_MAC_ADDR_2_REG ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dnet_readw_mac (struct dnet*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void dnet_get_hwaddr(struct dnet *bp)
{
	u16 tmp;
	u8 addr[6];

	/*
	 * from MAC docs:
	 * "Note that the MAC address is stored in the registers in Hexadecimal
	 * form. For example, to set the MAC Address to: AC-DE-48-00-00-80
	 * would require writing 0xAC (octet 0) to address 0x0B (high byte of
	 * Mac_addr[15:0]), 0xDE (octet 1) to address 0x0A (Low byte of
	 * Mac_addr[15:0]), 0x48 (octet 2) to address 0x0D (high byte of
	 * Mac_addr[15:0]), 0x00 (octet 3) to address 0x0C (Low byte of
	 * Mac_addr[15:0]), 0x00 (octet 4) to address 0x0F (high byte of
	 * Mac_addr[15:0]), and 0x80 (octet 5) to address * 0x0E (Low byte of
	 * Mac_addr[15:0]).
	 */
	tmp = dnet_readw_mac(bp, DNET_INTERNAL_MAC_ADDR_0_REG);
	*((__be16 *)addr) = cpu_to_be16(tmp);
	tmp = dnet_readw_mac(bp, DNET_INTERNAL_MAC_ADDR_1_REG);
	*((__be16 *)(addr + 2)) = cpu_to_be16(tmp);
	tmp = dnet_readw_mac(bp, DNET_INTERNAL_MAC_ADDR_2_REG);
	*((__be16 *)(addr + 4)) = cpu_to_be16(tmp);

	if (is_valid_ether_addr(addr))
		memcpy(bp->dev->dev_addr, addr, sizeof(addr));
}