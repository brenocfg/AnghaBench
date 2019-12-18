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
struct TYPE_2__ {int /*<<< orphan*/  str_vals; int /*<<< orphan*/  s; int /*<<< orphan*/  w; int /*<<< orphan*/  hw; int /*<<< orphan*/  b; } ;
struct wilc {TYPE_1__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void wilc_wlan_cfg_deinit(struct wilc *wl)
{
	kfree(wl->cfg.b);
	kfree(wl->cfg.hw);
	kfree(wl->cfg.w);
	kfree(wl->cfg.s);
	kfree(wl->cfg.str_vals);
}