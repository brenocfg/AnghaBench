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
struct btc_coexist {int /*<<< orphan*/  (* btc_set ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_SET_ACT_AGGREGATE_CTRL ; 
 int /*<<< orphan*/  BTC_SET_BL_BT_CTRL_AGG_SIZE ; 
 int /*<<< orphan*/  BTC_SET_BL_TO_REJ_AP_AGG_PKT ; 
 int /*<<< orphan*/  BTC_SET_U1_AGG_BUF_SIZE ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void halbtc8723b1ant_limited_rx(struct btc_coexist *btcoexist,
				       bool force_exec, bool rej_ap_agg_pkt,
				       bool bt_ctrl_agg_buf_size,
				       u8 agg_buf_size)
{
	bool reject_rx_agg = rej_ap_agg_pkt;
	bool bt_ctrl_rx_agg_size = bt_ctrl_agg_buf_size;
	u8 rxaggsize = agg_buf_size;

	/**********************************************
	 *	Rx Aggregation related setting
	 **********************************************/
	btcoexist->btc_set(btcoexist, BTC_SET_BL_TO_REJ_AP_AGG_PKT,
			   &reject_rx_agg);
	/* decide BT control aggregation buf size or not  */
	btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_CTRL_AGG_SIZE,
			   &bt_ctrl_rx_agg_size);
	/* aggregation buf size, only work
	 * when BT control Rx aggregation size.
	 */
	btcoexist->btc_set(btcoexist, BTC_SET_U1_AGG_BUF_SIZE, &rxaggsize);
	/* real update aggregation setting  */
	btcoexist->btc_set(btcoexist, BTC_SET_ACT_AGGREGATE_CTRL, NULL);
}