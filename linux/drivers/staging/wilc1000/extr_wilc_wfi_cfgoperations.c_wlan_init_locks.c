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
struct wilc {int /*<<< orphan*/  txq_thread_started; int /*<<< orphan*/  sync_event; int /*<<< orphan*/  cfg_event; int /*<<< orphan*/  txq_event; int /*<<< orphan*/  txq_add_to_head_cs; int /*<<< orphan*/  txq_spinlock; int /*<<< orphan*/  vif_mutex; int /*<<< orphan*/  cfg_cmd_lock; int /*<<< orphan*/  rxq_cs; int /*<<< orphan*/  hif_cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wlan_init_locks(struct wilc *wl)
{
	mutex_init(&wl->hif_cs);
	mutex_init(&wl->rxq_cs);
	mutex_init(&wl->cfg_cmd_lock);
	mutex_init(&wl->vif_mutex);

	spin_lock_init(&wl->txq_spinlock);
	mutex_init(&wl->txq_add_to_head_cs);

	init_completion(&wl->txq_event);
	init_completion(&wl->cfg_event);
	init_completion(&wl->sync_event);
	init_completion(&wl->txq_thread_started);
}