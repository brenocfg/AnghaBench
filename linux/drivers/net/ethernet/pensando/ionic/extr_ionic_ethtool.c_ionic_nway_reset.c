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
struct net_device {int dummy; } ;
struct ionic_lif {struct ionic* ionic; } ;
struct ionic {int /*<<< orphan*/  dev_cmd_lock; int /*<<< orphan*/  idev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVCMD_TIMEOUT ; 
 int /*<<< orphan*/  IONIC_PORT_ADMIN_STATE_DOWN ; 
 int /*<<< orphan*/  IONIC_PORT_ADMIN_STATE_UP ; 
 int /*<<< orphan*/  ionic_dev_cmd_port_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ionic_dev_cmd_wait (struct ionic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ionic_lif* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ionic_nway_reset(struct net_device *netdev)
{
	struct ionic_lif *lif = netdev_priv(netdev);
	struct ionic *ionic = lif->ionic;
	int err = 0;

	/* flap the link to force auto-negotiation */

	mutex_lock(&ionic->dev_cmd_lock);

	ionic_dev_cmd_port_state(&ionic->idev, IONIC_PORT_ADMIN_STATE_DOWN);
	err = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);

	if (!err) {
		ionic_dev_cmd_port_state(&ionic->idev, IONIC_PORT_ADMIN_STATE_UP);
		err = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);
	}

	mutex_unlock(&ionic->dev_cmd_lock);

	return err;
}