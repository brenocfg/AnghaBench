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
struct rtw_coex_stat {int wl_cck_lock; int wl_cck_lock_pre; int wl_cck_lock_ever; } ;
struct rtw_coex {struct rtw_coex_stat stat; } ;
struct rtw_dev {struct rtw_coex coex; } ;

/* Variables and functions */

__attribute__((used)) static void rtw_coex_wl_ccklock_detect(struct rtw_dev *rtwdev)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct rtw_coex_stat *coex_stat = &coex->stat;

	/* TODO: wait for rx_rate_change_notify implement */
	coex_stat->wl_cck_lock = false;
	coex_stat->wl_cck_lock_pre = false;
	coex_stat->wl_cck_lock_ever = false;
}