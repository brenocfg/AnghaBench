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
typedef  int u8 ;
struct rtl_tcb_desc {int rts_stbc; int cts_enable; int rts_bw; int rts_use_shortpreamble; int rts_use_shortgi; int rts_enable; int /*<<< orphan*/  rts_rate; scalar_t__ rts_sc; } ;
struct rtl_priv {TYPE_3__* cfg; } ;
struct TYPE_5__ {TYPE_1__* rates; } ;
struct ieee80211_tx_info {TYPE_2__ control; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * maps; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int IEEE80211_TX_RC_USE_CTS_PROTECT ; 
 int IEEE80211_TX_RC_USE_RTS_CTS ; 
 size_t RTL_RC_OFDM_RATE24M ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl_query_protection_mode(struct ieee80211_hw *hw,
				       struct rtl_tcb_desc *tcb_desc,
				       struct ieee80211_tx_info *info)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 rate_flag = info->control.rates[0].flags;

	/* Common Settings */
	tcb_desc->rts_stbc = false;
	tcb_desc->cts_enable = false;
	tcb_desc->rts_sc = 0;
	tcb_desc->rts_bw = false;
	tcb_desc->rts_use_shortpreamble = false;
	tcb_desc->rts_use_shortgi = false;

	if (rate_flag & IEEE80211_TX_RC_USE_CTS_PROTECT) {
		/* Use CTS-to-SELF in protection mode. */
		tcb_desc->rts_enable = true;
		tcb_desc->cts_enable = true;
		tcb_desc->rts_rate = rtlpriv->cfg->maps[RTL_RC_OFDM_RATE24M];
	} else if (rate_flag & IEEE80211_TX_RC_USE_RTS_CTS) {
		/* Use RTS-CTS in protection mode. */
		tcb_desc->rts_enable = true;
		tcb_desc->rts_rate = rtlpriv->cfg->maps[RTL_RC_OFDM_RATE24M];
	}
}