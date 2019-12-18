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
typedef  int u8 ;
struct rtl_priv {int dummy; } ;
struct TYPE_2__ {int reject_agg_pkt; int bt_ctrl_agg_buf_size; int agg_buf_size; } ;
struct btc_coexist {TYPE_1__ bt_info; } ;

/* Variables and functions */
 struct btc_coexist* rtl_btc_coexist (struct rtl_priv*) ; 

void rtl_btc_get_ampdu_cfg(struct rtl_priv *rtlpriv, u8 *reject_agg,
			   u8 *ctrl_agg_size, u8 *agg_size)
{
	struct btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	if (!btcoexist) {
		*reject_agg = false;
		*ctrl_agg_size = false;
		return;
	}

	if (reject_agg)
		*reject_agg = btcoexist->bt_info.reject_agg_pkt;
	if (ctrl_agg_size)
		*ctrl_agg_size = btcoexist->bt_info.bt_ctrl_agg_buf_size;
	if (agg_size)
		*agg_size = btcoexist->bt_info.agg_buf_size;
}