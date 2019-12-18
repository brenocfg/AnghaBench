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
typedef  int /*<<< orphan*/  u8 ;
struct rtl8169_private {struct net_device* dev; } ;
struct net_device {int /*<<< orphan*/ * dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC0 ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int eth_platform_get_mac_address (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl_rar_set (struct rtl8169_private*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl_read_mac_address (struct rtl8169_private*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl_read_mac_from_reg (struct rtl8169_private*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tp_to_dev (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl_init_mac_address(struct rtl8169_private *tp)
{
	struct net_device *dev = tp->dev;
	u8 *mac_addr = dev->dev_addr;
	int rc;

	rc = eth_platform_get_mac_address(tp_to_dev(tp), mac_addr);
	if (!rc)
		goto done;

	rtl_read_mac_address(tp, mac_addr);
	if (is_valid_ether_addr(mac_addr))
		goto done;

	rtl_read_mac_from_reg(tp, mac_addr, MAC0);
	if (is_valid_ether_addr(mac_addr))
		goto done;

	eth_hw_addr_random(dev);
	dev_warn(tp_to_dev(tp), "can't read MAC address, setting random one\n");
done:
	rtl_rar_set(tp, mac_addr);
}