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
struct rtl_pci {int* irq_mask; int irq_enabled; int sys_irq_mask; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_C2HEVT_CLEAR ; 
 int /*<<< orphan*/  REG_HIMR ; 
 int /*<<< orphan*/  REG_HIMRE ; 
 int /*<<< orphan*/  REG_HSIMR ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

void rtl88ee_enable_interrupt(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	rtl_write_dword(rtlpriv, REG_HIMR,
			rtlpci->irq_mask[0] & 0xFFFFFFFF);
	rtl_write_dword(rtlpriv, REG_HIMRE,
			rtlpci->irq_mask[1] & 0xFFFFFFFF);
	rtlpci->irq_enabled = true;
	/* there are some C2H CMDs have been sent
	 * before system interrupt is enabled, e.g., C2H, CPWM.
	 * So we need to clear all C2H events that FW has notified,
	 * otherwise FW won't schedule any commands anymore.
	 */
	rtl_write_byte(rtlpriv, REG_C2HEVT_CLEAR, 0);
	/*enable system interrupt*/
	rtl_write_dword(rtlpriv, REG_HSIMR,
			rtlpci->sys_irq_mask & 0xFFFFFFFF);
}