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
struct TYPE_2__ {int /*<<< orphan*/  delayed_listen_work; int /*<<< orphan*/  discovery_expired_work; int /*<<< orphan*/  discovery_timer; } ;
struct wil6210_vif {int /*<<< orphan*/  enable_tx_key_worker; int /*<<< orphan*/  probe_client_worker; TYPE_1__ p2p; int /*<<< orphan*/  disconnect_worker; int /*<<< orphan*/  scan_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wil_probe_client_flush (struct wil6210_vif*) ; 

__attribute__((used)) static void wil_vif_deinit(struct wil6210_vif *vif)
{
	del_timer_sync(&vif->scan_timer);
	del_timer_sync(&vif->p2p.discovery_timer);
	cancel_work_sync(&vif->disconnect_worker);
	cancel_work_sync(&vif->p2p.discovery_expired_work);
	cancel_work_sync(&vif->p2p.delayed_listen_work);
	wil_probe_client_flush(vif);
	cancel_work_sync(&vif->probe_client_worker);
	cancel_work_sync(&vif->enable_tx_key_worker);
}