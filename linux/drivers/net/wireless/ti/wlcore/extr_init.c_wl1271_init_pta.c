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
struct wl1271 {int /*<<< orphan*/  sg_enabled; } ;

/* Variables and functions */
 int wl1271_acx_sg_enable (struct wl1271*,int /*<<< orphan*/ ) ; 
 int wl12xx_acx_sg_cfg (struct wl1271*) ; 

int wl1271_init_pta(struct wl1271 *wl)
{
	int ret;

	ret = wl12xx_acx_sg_cfg(wl);
	if (ret < 0)
		return ret;

	ret = wl1271_acx_sg_enable(wl, wl->sg_enabled);
	if (ret < 0)
		return ret;

	return 0;
}