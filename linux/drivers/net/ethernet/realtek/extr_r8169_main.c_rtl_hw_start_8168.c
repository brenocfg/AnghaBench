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
struct rtl8169_private {scalar_t__ mac_version; int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EarlySize ; 
 int /*<<< orphan*/  IntrMitigate ; 
 int /*<<< orphan*/  MaxTxPacketSize ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL_NOSNOOP_EN ; 
 scalar_t__ RTL_GIGA_MAC_VER_13 ; 
 scalar_t__ RTL_GIGA_MAC_VER_16 ; 
 int /*<<< orphan*/  RTL_W16 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TxPacketMax ; 
 int /*<<< orphan*/  pcie_capability_set_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_hw_config (struct rtl8169_private*) ; 
 scalar_t__ rtl_is_8168evl_up (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl_hw_start_8168(struct rtl8169_private *tp)
{
	if (tp->mac_version == RTL_GIGA_MAC_VER_13 ||
	    tp->mac_version == RTL_GIGA_MAC_VER_16)
		pcie_capability_set_word(tp->pci_dev, PCI_EXP_DEVCTL,
					 PCI_EXP_DEVCTL_NOSNOOP_EN);

	if (rtl_is_8168evl_up(tp))
		RTL_W8(tp, MaxTxPacketSize, EarlySize);
	else
		RTL_W8(tp, MaxTxPacketSize, TxPacketMax);

	rtl_hw_config(tp);

	/* disable interrupt coalescing */
	RTL_W16(tp, IntrMitigate, 0x0000);
}