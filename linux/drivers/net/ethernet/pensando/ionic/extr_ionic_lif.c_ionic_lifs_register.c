#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * notifier_call; } ;
struct ionic {TYPE_2__* master_lif; int /*<<< orphan*/  dev; TYPE_1__ nb; int /*<<< orphan*/  nb_work; } ;
struct TYPE_4__ {int registered; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ionic_lif_notify ; 
 int /*<<< orphan*/  ionic_lif_notify_work ; 
 int /*<<< orphan*/  ionic_link_status_check_request (TYPE_2__*) ; 
 int register_netdev (int /*<<< orphan*/ ) ; 
 int register_netdevice_notifier (TYPE_1__*) ; 

int ionic_lifs_register(struct ionic *ionic)
{
	int err;

	INIT_WORK(&ionic->nb_work, ionic_lif_notify_work);

	ionic->nb.notifier_call = ionic_lif_notify;

	err = register_netdevice_notifier(&ionic->nb);
	if (err)
		ionic->nb.notifier_call = NULL;

	/* only register LIF0 for now */
	err = register_netdev(ionic->master_lif->netdev);
	if (err) {
		dev_err(ionic->dev, "Cannot register net device, aborting\n");
		return err;
	}

	ionic_link_status_check_request(ionic->master_lif);
	ionic->master_lif->registered = true;

	return 0;
}