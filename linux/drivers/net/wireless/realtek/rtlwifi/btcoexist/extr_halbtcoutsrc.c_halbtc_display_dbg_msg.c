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
struct seq_file {int dummy; } ;
struct btc_coexist {int dummy; } ;

/* Variables and functions */
#define  BTC_DBG_DISP_BT_LINK_INFO 130 
#define  BTC_DBG_DISP_COEX_STATISTICS 129 
#define  BTC_DBG_DISP_WIFI_STATUS 128 
 int /*<<< orphan*/  halbtc_display_bt_link_info (struct btc_coexist*,struct seq_file*) ; 
 int /*<<< orphan*/  halbtc_display_coex_statistics (struct btc_coexist*,struct seq_file*) ; 
 int /*<<< orphan*/  halbtc_display_wifi_status (struct btc_coexist*,struct seq_file*) ; 

__attribute__((used)) static void halbtc_display_dbg_msg(void *bt_context, u8 disp_type,
				   struct seq_file *m)
{
	struct btc_coexist *btcoexist = (struct btc_coexist *)bt_context;

	switch (disp_type) {
	case BTC_DBG_DISP_COEX_STATISTICS:
		halbtc_display_coex_statistics(btcoexist, m);
		break;
	case BTC_DBG_DISP_BT_LINK_INFO:
		halbtc_display_bt_link_info(btcoexist, m);
		break;
	case BTC_DBG_DISP_WIFI_STATUS:
		halbtc_display_wifi_status(btcoexist, m);
		break;
	default:
		break;
	}
}