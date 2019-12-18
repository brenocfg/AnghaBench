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
typedef  int u8 ;
struct rtl_hal {scalar_t__ hw_type; int /*<<< orphan*/  version; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum ht_channel_width { ____Placeholder_ht_channel_width } ht_channel_width ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ HARDWARE_TYPE_RTL8812AE ; 
 int HT_CHANNEL_WIDTH_20 ; 
 int HT_CHANNEL_WIDTH_20_40 ; 
 int HT_CHANNEL_WIDTH_80 ; 
 scalar_t__ IS_VENDOR_8812A_C_CUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RADC_BUF_CLK ; 
 int /*<<< orphan*/  RRFMOD ; 
 struct rtl_hal* rtl_hal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rtl8812ae_fixspur(struct ieee80211_hw *hw,
			      enum ht_channel_width band_width, u8 channel)
{
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	/*C cut Item12 ADC FIFO CLOCK*/
	if (IS_VENDOR_8812A_C_CUT(rtlhal->version)) {
		if (band_width == HT_CHANNEL_WIDTH_20_40 && channel == 11)
			rtl_set_bbreg(hw, RRFMOD, 0xC00, 0x3);
			/* 0x8AC[11:10] = 2'b11*/
		else
			rtl_set_bbreg(hw, RRFMOD, 0xC00, 0x2);
			/* 0x8AC[11:10] = 2'b10*/

		/* <20120914, Kordan> A workarould to resolve
		 * 2480Mhz spur by setting ADC clock as 160M. (Asked by Binson)
		 */
		if (band_width == HT_CHANNEL_WIDTH_20 &&
		    (channel == 13 || channel == 14)) {
			rtl_set_bbreg(hw, RRFMOD, 0x300, 0x3);
			/*0x8AC[9:8] = 2'b11*/
			rtl_set_bbreg(hw, RADC_BUF_CLK, BIT(30), 1);
			/* 0x8C4[30] = 1*/
		} else if (band_width == HT_CHANNEL_WIDTH_20_40 &&
			   channel == 11) {
			rtl_set_bbreg(hw, RADC_BUF_CLK, BIT(30), 1);
			/*0x8C4[30] = 1*/
		} else if (band_width != HT_CHANNEL_WIDTH_80) {
			rtl_set_bbreg(hw, RRFMOD, 0x300, 0x2);
			/*0x8AC[9:8] = 2'b10*/
			rtl_set_bbreg(hw, RADC_BUF_CLK, BIT(30), 0);
			/*0x8C4[30] = 0*/
		}
	} else if (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) {
		/* <20120914, Kordan> A workarould to resolve
		 * 2480Mhz spur by setting ADC clock as 160M.
		 */
		if (band_width == HT_CHANNEL_WIDTH_20 &&
		    (channel == 13 || channel == 14))
			rtl_set_bbreg(hw, RRFMOD, 0x300, 0x3);
			/*0x8AC[9:8] = 11*/
		else if (channel  <= 14) /*2.4G only*/
			rtl_set_bbreg(hw, RRFMOD, 0x300, 0x2);
			/*0x8AC[9:8] = 10*/
	}
}