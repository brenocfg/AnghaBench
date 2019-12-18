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
typedef  scalar_t__ u8 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_RXDESC ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 scalar_t__ DESC_RATEVHT1SS_MCS0 ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ get_rx_desc_rxmcs (int /*<<< orphan*/ *) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static bool rtl8821ae_get_rxdesc_is_vht(struct ieee80211_hw *hw, __le32 *pdesc)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 rx_rate = 0;

	rx_rate = get_rx_desc_rxmcs(pdesc);

	RT_TRACE(rtlpriv, COMP_RXDESC, DBG_LOUD, "rx_rate=0x%02x.\n", rx_rate);

	if (rx_rate >= DESC_RATEVHT1SS_MCS0)
		return true;
	return false;
}