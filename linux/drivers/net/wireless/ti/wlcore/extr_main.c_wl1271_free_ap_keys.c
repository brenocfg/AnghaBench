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
struct TYPE_2__ {int /*<<< orphan*/ ** recorded_keys; } ;
struct wl12xx_vif {TYPE_1__ ap; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int MAX_NUM_KEYS ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wl1271_free_ap_keys(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	int i;

	for (i = 0; i < MAX_NUM_KEYS; i++) {
		kfree(wlvif->ap.recorded_keys[i]);
		wlvif->ap.recorded_keys[i] = NULL;
	}
}