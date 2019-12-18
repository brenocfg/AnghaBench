#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * notifier_call; } ;
struct ionic {TYPE_2__* master_lif; TYPE_3__ nb; int /*<<< orphan*/  nb_work; } ;
struct TYPE_8__ {scalar_t__ reg_state; } ;
struct TYPE_5__ {int /*<<< orphan*/  work; } ;
struct TYPE_6__ {TYPE_4__* netdev; int /*<<< orphan*/  tx_timeout_work; TYPE_1__ deferred; } ;

/* Variables and functions */
 scalar_t__ NETREG_REGISTERED ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (TYPE_4__*) ; 
 int /*<<< orphan*/  unregister_netdevice_notifier (TYPE_3__*) ; 

void ionic_lifs_unregister(struct ionic *ionic)
{
	if (ionic->nb.notifier_call) {
		unregister_netdevice_notifier(&ionic->nb);
		cancel_work_sync(&ionic->nb_work);
		ionic->nb.notifier_call = NULL;
	}

	/* There is only one lif ever registered in the
	 * current model, so don't bother searching the
	 * ionic->lif for candidates to unregister
	 */
	cancel_work_sync(&ionic->master_lif->deferred.work);
	cancel_work_sync(&ionic->master_lif->tx_timeout_work);
	if (ionic->master_lif->netdev->reg_state == NETREG_REGISTERED)
		unregister_netdev(ionic->master_lif->netdev);
}