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
typedef  int u32 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int CV_CURVE_CNT ; 
 int /*<<< orphan*/  FINIT ; 
 int /*<<< orphan*/  INIT_IQK ; 
 int /*<<< orphan*/  RTPRINT (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int TARGET_CHNL_NUM_2G ; 
 int TARGET_CHNL_NUM_5G ; 
 int /*<<< orphan*/  _rtl92d_is_legal_5g_channel (struct ieee80211_hw*,int) ; 
 int _rtl92d_phy_get_abs (int,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl92d_phy_calc_curvindex(struct ieee80211_hw *hw,
				       u32 *targetchnl, u32 * curvecount_val,
				       bool is5g, u32 *curveindex)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u32 smallest_abs_val = 0xffffffff, u4tmp;
	u8 i, j;
	u8 chnl_num = is5g ? TARGET_CHNL_NUM_5G : TARGET_CHNL_NUM_2G;

	for (i = 0; i < chnl_num; i++) {
		if (is5g && !_rtl92d_is_legal_5g_channel(hw, i + 1))
			continue;
		curveindex[i] = 0;
		for (j = 0; j < (CV_CURVE_CNT * 2); j++) {
			u4tmp = _rtl92d_phy_get_abs(targetchnl[i],
				curvecount_val[j]);

			if (u4tmp < smallest_abs_val) {
				curveindex[i] = j;
				smallest_abs_val = u4tmp;
			}
		}
		smallest_abs_val = 0xffffffff;
		RTPRINT(rtlpriv, FINIT, INIT_IQK, "curveindex[%d] = %x\n",
			i, curveindex[i]);
	}
}