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
typedef  size_t u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_4__ {scalar_t__ rfoff_reason; } ;
struct TYPE_3__ {scalar_t__ driver_is_goingto_unload; } ;
struct rtl_priv {TYPE_2__ psc; TYPE_1__ rtlhal; } ;
struct rtl_pci {struct rtl8192_tx_ring* tx_ring; } ;
struct rtl8192_tx_ring {scalar_t__ cur_tx_rp; scalar_t__ cur_tx_wp; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 size_t BEACON_QUEUE ; 
 scalar_t__ RF_CHANGE_BY_PS ; 
 int /*<<< orphan*/  get_desc_addr_fr_q_idx (size_t) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 

bool rtl92ee_is_tx_desc_closed(struct ieee80211_hw *hw, u8 hw_queue, u16 index)
{
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u16 read_point, write_point;
	bool ret = false;
	static u8 stop_report_cnt;
	struct rtl8192_tx_ring *ring = &rtlpci->tx_ring[hw_queue];

	{
		u16 cur_tx_rp, cur_tx_wp;
		u32 tmpu32;

		tmpu32 =
		  rtl_read_dword(rtlpriv,
				 get_desc_addr_fr_q_idx(hw_queue));
		cur_tx_rp = (u16)((tmpu32 >> 16) & 0x0fff);
		cur_tx_wp = (u16)(tmpu32 & 0x0fff);

		/* don't need to update ring->cur_tx_wp */
		ring->cur_tx_rp = cur_tx_rp;
	}

	read_point = ring->cur_tx_rp;
	write_point = ring->cur_tx_wp;

	if (write_point > read_point) {
		if (index < write_point && index >= read_point)
			ret = false;
		else
			ret = true;
	} else if (write_point < read_point) {
		if (index > write_point && index < read_point)
			ret = true;
		else
			ret = false;
	} else {
		if (index != read_point)
			ret = true;
	}

	if (hw_queue == BEACON_QUEUE)
		ret = true;

	if (rtlpriv->rtlhal.driver_is_goingto_unload ||
	    rtlpriv->psc.rfoff_reason > RF_CHANGE_BY_PS)
		ret = true;

	if (hw_queue < BEACON_QUEUE) {
		if (!ret)
			stop_report_cnt++;
		else
			stop_report_cnt = 0;
	}

	return ret;
}