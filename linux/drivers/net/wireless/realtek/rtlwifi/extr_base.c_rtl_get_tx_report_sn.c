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
typedef  void* u16 ;
struct rtlwifi_tx_info {int /*<<< orphan*/  send_time; void* sn; } ;
struct rtl_tx_report {int /*<<< orphan*/  last_sent_time; void* last_sent_sn; int /*<<< orphan*/  sn; } ;
struct rtl_priv {struct rtl_tx_report tx_report; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_TX_REPORT ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static u16 rtl_get_tx_report_sn(struct ieee80211_hw *hw,
				struct rtlwifi_tx_info *tx_info)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_tx_report *tx_report = &rtlpriv->tx_report;
	u16 sn;

	/* SW_DEFINE[11:8] are reserved (driver fills zeros)
	 * SW_DEFINE[7:2] are used by driver
	 * SW_DEFINE[1:0] are reserved for firmware (driver fills zeros)
	 */
	sn = (atomic_inc_return(&tx_report->sn) & 0x003F) << 2;

	tx_report->last_sent_sn = sn;
	tx_report->last_sent_time = jiffies;
	tx_info->sn = sn;
	tx_info->send_time = tx_report->last_sent_time;
	RT_TRACE(rtlpriv, COMP_TX_REPORT, DBG_DMESG,
		 "Send TX-Report sn=0x%X\n", sn);

	return sn;
}