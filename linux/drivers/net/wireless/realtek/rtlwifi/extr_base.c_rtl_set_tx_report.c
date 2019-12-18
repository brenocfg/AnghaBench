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
typedef  int /*<<< orphan*/  u16 ;
struct rtlwifi_tx_info {int dummy; } ;
struct rtl_tcb_desc {scalar_t__ use_spe_rpt; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_TX_DESC_SPE_RPT (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_SW_DEFINE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_get_tx_report_sn (struct ieee80211_hw*,struct rtlwifi_tx_info*) ; 

void rtl_set_tx_report(struct rtl_tcb_desc *ptcb_desc, u8 *pdesc,
		       struct ieee80211_hw *hw, struct rtlwifi_tx_info *tx_info)
{
	if (ptcb_desc->use_spe_rpt) {
		u16 sn = rtl_get_tx_report_sn(hw, tx_info);

		SET_TX_DESC_SPE_RPT(pdesc, 1);
		SET_TX_DESC_SW_DEFINE(pdesc, sn);
	}
}