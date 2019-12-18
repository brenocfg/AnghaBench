#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ionic_lif {struct ionic* ionic; } ;
struct TYPE_6__ {TYPE_2__* port_info; } ;
struct ionic {int /*<<< orphan*/  dev_cmd_lock; TYPE_3__ idev; } ;
struct ethtool_pauseparam {scalar_t__ tx_pause; scalar_t__ rx_pause; scalar_t__ autoneg; } ;
struct TYPE_4__ {int /*<<< orphan*/  pause_type; } ;
struct TYPE_5__ {TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVCMD_TIMEOUT ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IONIC_PAUSE_F_RX ; 
 int /*<<< orphan*/  IONIC_PAUSE_F_TX ; 
 int /*<<< orphan*/  IONIC_PORT_PAUSE_TYPE_LINK ; 
 int /*<<< orphan*/  ionic_dev_cmd_port_pause (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ionic_dev_cmd_wait (struct ionic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ionic_lif* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ionic_set_pauseparam(struct net_device *netdev,
				struct ethtool_pauseparam *pause)
{
	struct ionic_lif *lif = netdev_priv(netdev);
	struct ionic *ionic = lif->ionic;
	u32 requested_pause;
	int err;

	if (pause->autoneg)
		return -EOPNOTSUPP;

	/* change both at the same time */
	requested_pause = IONIC_PORT_PAUSE_TYPE_LINK;
	if (pause->rx_pause)
		requested_pause |= IONIC_PAUSE_F_RX;
	if (pause->tx_pause)
		requested_pause |= IONIC_PAUSE_F_TX;

	if (requested_pause == lif->ionic->idev.port_info->config.pause_type)
		return 0;

	mutex_lock(&ionic->dev_cmd_lock);
	ionic_dev_cmd_port_pause(&lif->ionic->idev, requested_pause);
	err = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);
	mutex_unlock(&ionic->dev_cmd_lock);
	if (err)
		return err;

	return 0;
}