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
struct rtl_usb {int* irq_mask; } ;
struct rtl_priv {int dummy; } ;
struct rtl_pci {int* irq_mask; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_HARDWARE_TYPE_8192CE (struct rtl_priv*) ; 
 int /*<<< orphan*/  REG_HIMR ; 
 int /*<<< orphan*/  REG_HIMRE ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_usb* rtl_usbdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_usbpriv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

void rtl92c_enable_interrupt(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));

	if (IS_HARDWARE_TYPE_8192CE(rtlpriv)) {
		rtl_write_dword(rtlpriv, REG_HIMR, rtlpci->irq_mask[0] &
				0xFFFFFFFF);
		rtl_write_dword(rtlpriv, REG_HIMRE, rtlpci->irq_mask[1] &
				0xFFFFFFFF);
	} else {
		rtl_write_dword(rtlpriv, REG_HIMR, rtlusb->irq_mask[0] &
				0xFFFFFFFF);
		rtl_write_dword(rtlpriv, REG_HIMRE, rtlusb->irq_mask[1] &
				0xFFFFFFFF);
	}
}