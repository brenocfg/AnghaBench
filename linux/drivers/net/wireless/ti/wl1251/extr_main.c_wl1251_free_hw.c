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
struct wl1251 {int /*<<< orphan*/  hw; int /*<<< orphan*/ * rx_descriptor; int /*<<< orphan*/ * nvs; int /*<<< orphan*/ * fw; int /*<<< orphan*/ * data_path; int /*<<< orphan*/ * target_mem_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_free_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl1251_debugfs_exit (struct wl1251*) ; 

int wl1251_free_hw(struct wl1251 *wl)
{
	ieee80211_unregister_hw(wl->hw);

	wl1251_debugfs_exit(wl);

	kfree(wl->target_mem_map);
	kfree(wl->data_path);
	vfree(wl->fw);
	wl->fw = NULL;
	kfree(wl->nvs);
	wl->nvs = NULL;

	kfree(wl->rx_descriptor);
	wl->rx_descriptor = NULL;

	ieee80211_free_hw(wl->hw);

	return 0;
}