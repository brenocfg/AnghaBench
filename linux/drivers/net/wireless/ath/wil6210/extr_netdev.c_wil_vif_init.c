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
struct wil6210_vif {int bcast_ring; int net_queue_stopped; int /*<<< orphan*/  probe_client_pending; int /*<<< orphan*/  enable_tx_key_worker; TYPE_1__ p2p; int /*<<< orphan*/  disconnect_worker; int /*<<< orphan*/  probe_client_worker; int /*<<< orphan*/  scan_timer; int /*<<< orphan*/  connect_timer; int /*<<< orphan*/  probe_client_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_connect_timer_fn ; 
 int /*<<< orphan*/  wil_disconnect_worker ; 
 int /*<<< orphan*/  wil_enable_tx_key_worker ; 
 int /*<<< orphan*/  wil_p2p_delayed_listen_work ; 
 int /*<<< orphan*/  wil_p2p_discovery_timer_fn ; 
 int /*<<< orphan*/  wil_p2p_listen_expired ; 
 int /*<<< orphan*/  wil_probe_client_worker ; 
 int /*<<< orphan*/  wil_scan_timer_fn ; 

__attribute__((used)) static void wil_vif_init(struct wil6210_vif *vif)
{
	vif->bcast_ring = -1;

	mutex_init(&vif->probe_client_mutex);

	timer_setup(&vif->connect_timer, wil_connect_timer_fn, 0);
	timer_setup(&vif->scan_timer, wil_scan_timer_fn, 0);
	timer_setup(&vif->p2p.discovery_timer, wil_p2p_discovery_timer_fn, 0);

	INIT_WORK(&vif->probe_client_worker, wil_probe_client_worker);
	INIT_WORK(&vif->disconnect_worker, wil_disconnect_worker);
	INIT_WORK(&vif->p2p.discovery_expired_work, wil_p2p_listen_expired);
	INIT_WORK(&vif->p2p.delayed_listen_work, wil_p2p_delayed_listen_work);
	INIT_WORK(&vif->enable_tx_key_worker, wil_enable_tx_key_worker);

	INIT_LIST_HEAD(&vif->probe_client_pending);

	vif->net_queue_stopped = 1;
}