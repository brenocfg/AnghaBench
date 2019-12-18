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
struct btc_coexist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_PS_WIFI_NATIVE ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  btc8821a1ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc8821a1ant_ignore_wlan_act (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc8821a1ant_limited_rx (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  btc8821a1ant_limited_tx (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc8821a1ant_power_save_state (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  btc8821a1ant_ps_tdma (struct btc_coexist*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void btc8821a1ant_coex_under_5g(struct btc_coexist *btcoexist)
{
	btc8821a1ant_power_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
				      0x0, 0x0);
	btc8821a1ant_ignore_wlan_act(btcoexist, NORMAL_EXEC, true);

	btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 10);

	btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);

	btc8821a1ant_limited_tx(btcoexist, NORMAL_EXEC, 0, 0, 0, 0);

	btc8821a1ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 5);
}