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
struct r8192_priv {int /*<<< orphan*/  qos_activate; int /*<<< orphan*/  reset_wq; TYPE_1__* rtllib; int /*<<< orphan*/  update_beacon_wq; int /*<<< orphan*/  watch_dog_wq; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_sleep_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _rtl92e_cancel_deferred_work(struct r8192_priv *priv)
{
	cancel_delayed_work_sync(&priv->watch_dog_wq);
	cancel_delayed_work_sync(&priv->update_beacon_wq);
	cancel_delayed_work(&priv->rtllib->hw_sleep_wq);
	cancel_work_sync(&priv->reset_wq);
	cancel_work_sync(&priv->qos_activate);
}