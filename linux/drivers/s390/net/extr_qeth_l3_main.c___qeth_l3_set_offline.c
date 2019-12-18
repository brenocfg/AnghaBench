#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ cq; } ;
struct TYPE_8__ {int hwtrap; int open_when_online; } ;
struct qeth_card {int /*<<< orphan*/  discipline_mutex; int /*<<< orphan*/  conf_mutex; TYPE_3__* dev; TYPE_2__ options; TYPE_1__ info; } ;
struct TYPE_11__ {int /*<<< orphan*/  kobj; } ;
struct ccwgroup_device {TYPE_5__ dev; } ;
struct TYPE_10__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_DDEV (struct qeth_card*) ; 
 int /*<<< orphan*/  CARD_RDEV (struct qeth_card*) ; 
 int /*<<< orphan*/  CARD_WDEV (struct qeth_card*) ; 
 int IFF_UP ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  NETDEV_REBOOT ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,int) ; 
 scalar_t__ QETH_CQ_ENABLED ; 
 int /*<<< orphan*/  QETH_DIAGS_TRAP_DISARM ; 
 int /*<<< orphan*/  call_netdevice_notifiers (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int ccw_device_set_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_close (TYPE_3__*) ; 
 struct qeth_card* dev_get_drvdata (TYPE_5__*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (TYPE_3__*) ; 
 int /*<<< orphan*/  netif_device_detach (TYPE_3__*) ; 
 int /*<<< orphan*/  qdio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_hw_trap (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_l3_stop_card (struct qeth_card*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int __qeth_l3_set_offline(struct ccwgroup_device *cgdev,
			int recovery_mode)
{
	struct qeth_card *card = dev_get_drvdata(&cgdev->dev);
	int rc = 0, rc2 = 0, rc3 = 0;

	mutex_lock(&card->discipline_mutex);
	mutex_lock(&card->conf_mutex);
	QETH_CARD_TEXT(card, 3, "setoffl");

	if ((!recovery_mode && card->info.hwtrap) || card->info.hwtrap == 2) {
		qeth_hw_trap(card, QETH_DIAGS_TRAP_DISARM);
		card->info.hwtrap = 1;
	}

	rtnl_lock();
	card->info.open_when_online = card->dev->flags & IFF_UP;
	dev_close(card->dev);
	netif_device_detach(card->dev);
	netif_carrier_off(card->dev);
	rtnl_unlock();

	qeth_l3_stop_card(card);
	if (card->options.cq == QETH_CQ_ENABLED) {
		rtnl_lock();
		call_netdevice_notifiers(NETDEV_REBOOT, card->dev);
		rtnl_unlock();
	}
	rc  = ccw_device_set_offline(CARD_DDEV(card));
	rc2 = ccw_device_set_offline(CARD_WDEV(card));
	rc3 = ccw_device_set_offline(CARD_RDEV(card));
	if (!rc)
		rc = (rc2) ? rc2 : rc3;
	if (rc)
		QETH_CARD_TEXT_(card, 2, "1err%d", rc);
	qdio_free(CARD_DDEV(card));

	/* let user_space know that device is offline */
	kobject_uevent(&cgdev->dev.kobj, KOBJ_CHANGE);
	mutex_unlock(&card->conf_mutex);
	mutex_unlock(&card->discipline_mutex);
	return 0;
}