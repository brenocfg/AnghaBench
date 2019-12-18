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
struct wl1251 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WL1251_PSM_CAM ; 
 int wl1251_acx_sleep_auth (struct wl1251*,int /*<<< orphan*/ ) ; 

int wl1251_hw_init_power_auth(struct wl1251 *wl)
{
	return wl1251_acx_sleep_auth(wl, WL1251_PSM_CAM);
}