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
typedef  scalar_t__ u32 ;
struct wilc_vif {scalar_t__ ndev; scalar_t__ mac_opened; } ;
struct wilc {int vif_num; int /*<<< orphan*/  vif_mutex; struct wilc_vif** vif; scalar_t__ close; int /*<<< orphan*/  txq_thread_started; int /*<<< orphan*/  txq_event; } ;

/* Variables and functions */
 int ENOBUFS ; 
 scalar_t__ FLOW_CONTROL_LOWER_THRESHOLD ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_wake_queue (scalar_t__) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int wilc_wlan_handle_txq (struct wilc*,scalar_t__*) ; 

__attribute__((used)) static int wilc_txq_task(void *vp)
{
	int ret;
	u32 txq_count;
	struct wilc *wl = vp;

	complete(&wl->txq_thread_started);
	while (1) {
		wait_for_completion(&wl->txq_event);

		if (wl->close) {
			complete(&wl->txq_thread_started);

			while (!kthread_should_stop())
				schedule();
			break;
		}
		do {
			ret = wilc_wlan_handle_txq(wl, &txq_count);
			if (txq_count < FLOW_CONTROL_LOWER_THRESHOLD) {
				int i;
				struct wilc_vif *ifc;

				mutex_lock(&wl->vif_mutex);
				for (i = 0; i < wl->vif_num; i++) {
					ifc = wl->vif[i];
					if (ifc->mac_opened && ifc->ndev)
						netif_wake_queue(ifc->ndev);
				}
				mutex_unlock(&wl->vif_mutex);
			}
		} while (ret == -ENOBUFS && !wl->close);
	}
	return 0;
}