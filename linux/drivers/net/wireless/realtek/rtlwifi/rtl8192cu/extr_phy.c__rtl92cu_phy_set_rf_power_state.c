#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u32 ;
struct rtl_ps_ctl {int rfpwr_state; void* last_sleep_jiffies; void* last_awake_jiffies; int reg_rfps_level; int /*<<< orphan*/  rfoff_reason; } ;
struct rtl_priv {TYPE_2__* cfg; } ;
struct TYPE_6__ {struct rtl8192_tx_ring* tx_ring; } ;
struct rtl_pci_priv {TYPE_3__ dev; } ;
struct rtl_mac {int /*<<< orphan*/  link_state; } ;
struct rtl8192_tx_ring {int /*<<< orphan*/  queue; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum rf_pwrstate { ____Placeholder_rf_pwrstate } rf_pwrstate ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* led_control ) (struct ieee80211_hw*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 size_t BEACON_QUEUE ; 
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  COMP_RF ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  DBG_WARNING ; 
#define  ERFOFF 130 
#define  ERFON 129 
#define  ERFSLEEP 128 
 int /*<<< orphan*/  LED_CTL_LINK ; 
 int /*<<< orphan*/  LED_CTL_NO_LINK ; 
 int /*<<< orphan*/  LED_CTL_POWER_OFF ; 
 int /*<<< orphan*/  MAC80211_LINKED ; 
 size_t MAX_DOZE_WAITING_TIMES_9x ; 
 int /*<<< orphan*/  RF_CHANGE_BY_IPS ; 
 size_t RTL_PCI_MAX_TX_QUEUE_COUNT ; 
 int /*<<< orphan*/  RT_CLEAR_PS_LEVEL (struct rtl_ps_ctl*,int) ; 
 int /*<<< orphan*/  RT_IN_PS_LEVEL (struct rtl_ps_ctl*,int) ; 
 int RT_RF_OFF_LEVL_HALT_NIC ; 
 int /*<<< orphan*/  RT_SET_PS_LEVEL (struct rtl_ps_ctl*,int) ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  _rtl92c_phy_set_rf_sleep (struct ieee80211_hw*) ; 
 void* jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (void*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  rtl92ce_phy_set_rf_on (struct ieee80211_hw*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_pci_priv* rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_ps_disable_nic (struct ieee80211_hw*) ; 
 int rtl_ps_enable_nic (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int /*<<< orphan*/  skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool _rtl92cu_phy_set_rf_power_state(struct ieee80211_hw *hw,
					    enum rf_pwrstate rfpwr_state)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci_priv *pcipriv = rtl_pcipriv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool bresult = true;
	u8 i, queue_id;
	struct rtl8192_tx_ring *ring = NULL;

	switch (rfpwr_state) {
	case ERFON:
		if ((ppsc->rfpwr_state == ERFOFF) &&
		    RT_IN_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC)) {
			bool rtstatus;
			u32 init_count = 0;

			do {
				init_count++;
				RT_TRACE(rtlpriv, COMP_RF, DBG_DMESG,
					 "IPS Set eRf nic enable\n");
				rtstatus = rtl_ps_enable_nic(hw);
			} while (!rtstatus && (init_count < 10));
			RT_CLEAR_PS_LEVEL(ppsc,
					  RT_RF_OFF_LEVL_HALT_NIC);
		} else {
			RT_TRACE(rtlpriv, COMP_RF, DBG_DMESG,
				 "Set ERFON sleeped:%d ms\n",
				 jiffies_to_msecs(jiffies -
						  ppsc->last_sleep_jiffies));
			ppsc->last_awake_jiffies = jiffies;
			rtl92ce_phy_set_rf_on(hw);
		}
		if (mac->link_state == MAC80211_LINKED) {
			rtlpriv->cfg->ops->led_control(hw,
						       LED_CTL_LINK);
		} else {
			rtlpriv->cfg->ops->led_control(hw,
						       LED_CTL_NO_LINK);
		}
		break;
	case ERFOFF:
		for (queue_id = 0, i = 0;
		     queue_id < RTL_PCI_MAX_TX_QUEUE_COUNT;) {
			ring = &pcipriv->dev.tx_ring[queue_id];
			if (skb_queue_len(&ring->queue) == 0 ||
				queue_id == BEACON_QUEUE) {
				queue_id++;
				continue;
			} else {
				RT_TRACE(rtlpriv, COMP_ERR, DBG_WARNING,
					 "eRf Off/Sleep: %d times TcbBusyQueue[%d] =%d before doze!\n",
					 i + 1,
					 queue_id,
					 skb_queue_len(&ring->queue));
				udelay(10);
				i++;
			}
			if (i >= MAX_DOZE_WAITING_TIMES_9x) {
				RT_TRACE(rtlpriv, COMP_ERR, DBG_WARNING,
					 "ERFOFF: %d times TcbBusyQueue[%d] = %d !\n",
					 MAX_DOZE_WAITING_TIMES_9x,
					 queue_id,
					 skb_queue_len(&ring->queue));
				break;
			}
		}
		if (ppsc->reg_rfps_level & RT_RF_OFF_LEVL_HALT_NIC) {
			RT_TRACE(rtlpriv, COMP_RF, DBG_DMESG,
				 "IPS Set eRf nic disable\n");
			rtl_ps_disable_nic(hw);
			RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC);
		} else {
			if (ppsc->rfoff_reason == RF_CHANGE_BY_IPS) {
				rtlpriv->cfg->ops->led_control(hw,
							 LED_CTL_NO_LINK);
			} else {
				rtlpriv->cfg->ops->led_control(hw,
							 LED_CTL_POWER_OFF);
			}
		}
		break;
	case ERFSLEEP:
		if (ppsc->rfpwr_state == ERFOFF)
			return false;
		for (queue_id = 0, i = 0;
		     queue_id < RTL_PCI_MAX_TX_QUEUE_COUNT;) {
			ring = &pcipriv->dev.tx_ring[queue_id];
			if (skb_queue_len(&ring->queue) == 0) {
				queue_id++;
				continue;
			} else {
				RT_TRACE(rtlpriv, COMP_ERR, DBG_WARNING,
					 "eRf Off/Sleep: %d times TcbBusyQueue[%d] =%d before doze!\n",
					 i + 1, queue_id,
					 skb_queue_len(&ring->queue));
				udelay(10);
				i++;
			}
			if (i >= MAX_DOZE_WAITING_TIMES_9x) {
				RT_TRACE(rtlpriv, COMP_ERR, DBG_WARNING,
					 "ERFSLEEP: %d times TcbBusyQueue[%d] = %d !\n",
					 MAX_DOZE_WAITING_TIMES_9x,
					 queue_id,
					 skb_queue_len(&ring->queue));
				break;
			}
		}
		RT_TRACE(rtlpriv, COMP_RF, DBG_DMESG,
			 "Set ERFSLEEP awaked:%d ms\n",
			 jiffies_to_msecs(jiffies - ppsc->last_awake_jiffies));
		ppsc->last_sleep_jiffies = jiffies;
		_rtl92c_phy_set_rf_sleep(hw);
		break;
	default:
		pr_err("switch case %#x not processed\n",
		       rfpwr_state);
		bresult = false;
		break;
	}
	if (bresult)
		ppsc->rfpwr_state = rfpwr_state;
	return bresult;
}