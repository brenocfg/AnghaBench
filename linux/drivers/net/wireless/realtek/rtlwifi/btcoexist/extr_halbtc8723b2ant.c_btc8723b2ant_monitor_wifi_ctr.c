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
struct btc_coexist {int /*<<< orphan*/  (* btc_write_1byte_bitmask ) (struct btc_coexist*,int,int,int) ;scalar_t__ (* btc_read_2byte ) (struct btc_coexist*,int) ;scalar_t__ (* btc_read_4byte ) (struct btc_coexist*,int) ;} ;
struct TYPE_2__ {scalar_t__ crc_err_11n_agg; scalar_t__ crc_err_11n; scalar_t__ crc_err_11g; scalar_t__ crc_err_cck; scalar_t__ crc_ok_11n_agg; scalar_t__ crc_ok_11n; scalar_t__ crc_ok_11g; scalar_t__ crc_ok_cck; scalar_t__ under_ips; } ;

/* Variables and functions */
 TYPE_1__* coex_sta ; 
 scalar_t__ stub1 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub10 (struct btc_coexist*,int,int,int) ; 
 scalar_t__ stub2 (struct btc_coexist*,int) ; 
 scalar_t__ stub3 (struct btc_coexist*,int) ; 
 scalar_t__ stub4 (struct btc_coexist*,int) ; 
 scalar_t__ stub5 (struct btc_coexist*,int) ; 
 scalar_t__ stub6 (struct btc_coexist*,int) ; 
 scalar_t__ stub7 (struct btc_coexist*,int) ; 
 scalar_t__ stub8 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub9 (struct btc_coexist*,int,int,int) ; 

__attribute__((used)) static void btc8723b2ant_monitor_wifi_ctr(struct btc_coexist *btcoexist)
{
	if (coex_sta->under_ips) {
		coex_sta->crc_ok_cck = 0;
		coex_sta->crc_ok_11g = 0;
		coex_sta->crc_ok_11n = 0;
		coex_sta->crc_ok_11n_agg = 0;

		coex_sta->crc_err_cck = 0;
		coex_sta->crc_err_11g = 0;
		coex_sta->crc_err_11n = 0;
		coex_sta->crc_err_11n_agg = 0;
	} else {
		coex_sta->crc_ok_cck =
			btcoexist->btc_read_4byte(btcoexist, 0xf88);
		coex_sta->crc_ok_11g =
			btcoexist->btc_read_2byte(btcoexist, 0xf94);
		coex_sta->crc_ok_11n =
			btcoexist->btc_read_2byte(btcoexist, 0xf90);
		coex_sta->crc_ok_11n_agg =
			btcoexist->btc_read_2byte(btcoexist, 0xfb8);

		coex_sta->crc_err_cck =
			btcoexist->btc_read_4byte(btcoexist, 0xf84);
		coex_sta->crc_err_11g =
			btcoexist->btc_read_2byte(btcoexist, 0xf96);
		coex_sta->crc_err_11n =
			btcoexist->btc_read_2byte(btcoexist, 0xf92);
		coex_sta->crc_err_11n_agg =
			btcoexist->btc_read_2byte(btcoexist, 0xfba);
	}

	/* reset counter */
	btcoexist->btc_write_1byte_bitmask(btcoexist, 0xf16, 0x1, 0x1);
	btcoexist->btc_write_1byte_bitmask(btcoexist, 0xf16, 0x1, 0x0);
}