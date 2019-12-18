#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_2__ {scalar_t__ cck_inch14; } ;
struct rtl_priv {TYPE_1__ dm; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int CCK_TABLE_LENGTH ; 
 int /*<<< orphan*/  COMP_POWER_TRACKING ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 long MASKCCK ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int /*<<< orphan*/  RCCK0_TXFILTER2 ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,long,scalar_t__,scalar_t__) ; 
 scalar_t__** cckswing_table_ch14 ; 
 scalar_t__** cckswing_table_ch1ch13 ; 
 long le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl92d_acquire_cckandrw_pagea_ctl (struct ieee80211_hw*,unsigned long*) ; 
 int /*<<< orphan*/  rtl92d_release_cckandrw_pagea_ctl (struct ieee80211_hw*,unsigned long*) ; 
 long rtl_get_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl92d_bandtype_2_4G(struct ieee80211_hw *hw, long *temp_cckg,
				 u8 *cck_index_old)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	int i;
	unsigned long flag = 0;
	long temp_cck;
	const u8 *cckswing;

	/* Query CCK default setting From 0xa24 */
	rtl92d_acquire_cckandrw_pagea_ctl(hw, &flag);
	temp_cck = rtl_get_bbreg(hw, RCCK0_TXFILTER2,
				 MASKDWORD) & MASKCCK;
	rtl92d_release_cckandrw_pagea_ctl(hw, &flag);
	for (i = 0; i < CCK_TABLE_LENGTH; i++) {
		if (rtlpriv->dm.cck_inch14)
			cckswing = &cckswing_table_ch14[i][2];
		else
			cckswing = &cckswing_table_ch1ch13[i][2];

		if (temp_cck == le32_to_cpu(*((__le32 *)cckswing))) {
			*cck_index_old = (u8)i;
			RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				 "Initial reg0x%x = 0x%lx, cck_index = 0x%x, ch14 %d\n",
				 RCCK0_TXFILTER2, temp_cck,
				 *cck_index_old,
				 rtlpriv->dm.cck_inch14);
			break;
		}
	}
	*temp_cckg = temp_cck;
}