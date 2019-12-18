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
struct TYPE_2__ {int bt_ctrl_lps; } ;
struct btc_coexist {TYPE_1__ bt_info; } ;

/* Variables and functions */

__attribute__((used)) static void halbtc_post_normal_lps(struct btc_coexist *btcoexist)
{
	if (btcoexist->bt_info.bt_ctrl_lps)
		btcoexist->bt_info.bt_ctrl_lps = false;
}