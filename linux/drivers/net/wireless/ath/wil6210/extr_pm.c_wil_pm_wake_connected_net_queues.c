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
struct wil6210_vif {int /*<<< orphan*/  status; } ;
struct wil6210_priv {int /*<<< orphan*/  vif_mutex; struct wil6210_vif** vifs; } ;

/* Variables and functions */
 int GET_MAX_VIFS (struct wil6210_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_update_net_queues_bh (struct wil6210_priv*,struct wil6210_vif*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wil_vif_fwconnected ; 

__attribute__((used)) static void wil_pm_wake_connected_net_queues(struct wil6210_priv *wil)
{
	int i;

	mutex_lock(&wil->vif_mutex);
	for (i = 0; i < GET_MAX_VIFS(wil); i++) {
		struct wil6210_vif *vif = wil->vifs[i];

		if (vif && test_bit(wil_vif_fwconnected, vif->status))
			wil_update_net_queues_bh(wil, vif, NULL, false);
	}
	mutex_unlock(&wil->vif_mutex);
}