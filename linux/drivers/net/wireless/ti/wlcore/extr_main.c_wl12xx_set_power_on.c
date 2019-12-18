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
struct wl1271 {int /*<<< orphan*/ * ptable; } ;

/* Variables and functions */
 size_t PART_BOOT ; 
 int /*<<< orphan*/  WL1271_POWER_ON_SLEEP ; 
 int /*<<< orphan*/  WL1271_PRE_POWER_ON_SLEEP ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_io_init (struct wl1271*) ; 
 int /*<<< orphan*/  wl1271_io_reset (struct wl1271*) ; 
 int /*<<< orphan*/  wl1271_power_off (struct wl1271*) ; 
 int wl1271_power_on (struct wl1271*) ; 
 int wlcore_fw_wakeup (struct wl1271*) ; 
 int wlcore_set_partition (struct wl1271*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wl12xx_set_power_on(struct wl1271 *wl)
{
	int ret;

	msleep(WL1271_PRE_POWER_ON_SLEEP);
	ret = wl1271_power_on(wl);
	if (ret < 0)
		goto out;
	msleep(WL1271_POWER_ON_SLEEP);
	wl1271_io_reset(wl);
	wl1271_io_init(wl);

	ret = wlcore_set_partition(wl, &wl->ptable[PART_BOOT]);
	if (ret < 0)
		goto fail;

	/* ELP module wake up */
	ret = wlcore_fw_wakeup(wl);
	if (ret < 0)
		goto fail;

out:
	return ret;

fail:
	wl1271_power_off(wl);
	return ret;
}