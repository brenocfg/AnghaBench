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
struct rtl_priv {int dummy; } ;
struct rtl_pci {int /*<<< orphan*/  receive_config; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int COMP_INIT ; 
 int COMP_TURBO ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RCR_AAP ; 
 int /*<<< orphan*/  REG_RCR ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtl8821ae_allow_all_destaddr(struct ieee80211_hw *hw,
	bool allow_all_da, bool write_into_reg)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	if (allow_all_da) /* Set BIT0 */
		rtlpci->receive_config |= RCR_AAP;
	else /* Clear BIT0 */
		rtlpci->receive_config &= ~RCR_AAP;

	if (write_into_reg)
		rtl_write_dword(rtlpriv, REG_RCR, rtlpci->receive_config);

	RT_TRACE(rtlpriv, COMP_TURBO | COMP_INIT, DBG_LOUD,
		"receive_config=0x%08X, write_into_reg=%d\n",
		rtlpci->receive_config, write_into_reg);
}