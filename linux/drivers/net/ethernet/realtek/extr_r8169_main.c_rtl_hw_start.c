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
struct rtl8169_private {scalar_t__ mac_version; TYPE_1__* dev; int /*<<< orphan*/  cp_cmd; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPCMD_MASK ; 
 int /*<<< orphan*/  CPlusCmd ; 
 int /*<<< orphan*/  ChipCmd ; 
 int CmdRxEnb ; 
 int CmdTxEnb ; 
 scalar_t__ RTL_GIGA_MAC_VER_06 ; 
 int /*<<< orphan*/  RTL_R16 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W16 (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_hw_start_8125 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8168 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8169 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_init_rxcfg (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_irq_enable (struct rtl8169_private*) ; 
 scalar_t__ rtl_is_8125 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_jumbo_config (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_lock_config_regs (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_set_rx_max_size (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_set_rx_mode (TYPE_1__*) ; 
 int /*<<< orphan*/  rtl_set_rx_tx_desc_registers (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_set_tx_config_registers (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_unlock_config_regs (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl_hw_start(struct  rtl8169_private *tp)
{
	rtl_unlock_config_regs(tp);

	tp->cp_cmd &= CPCMD_MASK;
	RTL_W16(tp, CPlusCmd, tp->cp_cmd);

	if (tp->mac_version <= RTL_GIGA_MAC_VER_06)
		rtl_hw_start_8169(tp);
	else if (rtl_is_8125(tp))
		rtl_hw_start_8125(tp);
	else
		rtl_hw_start_8168(tp);

	rtl_set_rx_max_size(tp);
	rtl_set_rx_tx_desc_registers(tp);
	rtl_lock_config_regs(tp);

	rtl_jumbo_config(tp, tp->dev->mtu);

	/* Initially a 10 us delay. Turned it into a PCI commit. - FR */
	RTL_R16(tp, CPlusCmd);
	RTL_W8(tp, ChipCmd, CmdTxEnb | CmdRxEnb);
	rtl_init_rxcfg(tp);
	rtl_set_tx_config_registers(tp);
	rtl_set_rx_mode(tp->dev);
	rtl_irq_enable(tp);
}