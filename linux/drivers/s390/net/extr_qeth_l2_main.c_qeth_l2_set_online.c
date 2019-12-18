#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ open_when_online; scalar_t__ hwtrap; } ;
struct TYPE_6__ {scalar_t__ supported_funcs; } ;
struct TYPE_7__ {TYPE_1__ sbp; } ;
struct qeth_card {int /*<<< orphan*/  discipline_mutex; int /*<<< orphan*/  conf_mutex; TYPE_4__ info; int /*<<< orphan*/  state; TYPE_3__* gdev; TYPE_2__ options; struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  kobj; } ;
struct ccwgroup_device {TYPE_5__ dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_DDEV (struct qeth_card*) ; 
 int /*<<< orphan*/  CARD_RDEV (struct qeth_card*) ; 
 int /*<<< orphan*/  CARD_STATE_HARDSETUP ; 
 int /*<<< orphan*/  CARD_STATE_SOFTSETUP ; 
 int /*<<< orphan*/  CARD_WDEV (struct qeth_card*) ; 
 int ENODEV ; 
 scalar_t__ IS_OSD (struct qeth_card*) ; 
 scalar_t__ IS_OSX (struct qeth_card*) ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,int) ; 
 int /*<<< orphan*/  QETH_DIAGS_CMD_TRAP ; 
 int /*<<< orphan*/  QETH_DIAGS_TRAP_ARM ; 
 int /*<<< orphan*/  ccw_device_set_offline (int /*<<< orphan*/ ) ; 
 struct qeth_card* dev_get_drvdata (TYPE_5__*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_open (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 int /*<<< orphan*/  qdio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_bridgeport_query_support (struct qeth_card*) ; 
 int qeth_core_hardsetup_card (struct qeth_card*,int*) ; 
 int /*<<< orphan*/  qeth_enable_hw_features (struct net_device*) ; 
 scalar_t__ qeth_hw_trap (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int qeth_init_qdio_queues (struct qeth_card*) ; 
 scalar_t__ qeth_is_diagass_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_l2_register_dev_addr (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_l2_setup_bridgeport_attrs (struct qeth_card*) ; 
 int qeth_l2_setup_netdev (struct qeth_card*,int) ; 
 int qeth_l2_start_ipassists (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_l2_stop_card (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_l2_trace_features (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_l2_vnicc_init (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_netdev_is_registered (struct net_device*) ; 
 int /*<<< orphan*/  qeth_print_status_message (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_set_allowed_threads (struct qeth_card*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_trace_features (struct qeth_card*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int qeth_l2_set_online(struct ccwgroup_device *gdev)
{
	struct qeth_card *card = dev_get_drvdata(&gdev->dev);
	struct net_device *dev = card->dev;
	int rc = 0;
	bool carrier_ok;

	mutex_lock(&card->discipline_mutex);
	mutex_lock(&card->conf_mutex);
	QETH_CARD_TEXT(card, 2, "setonlin");

	rc = qeth_core_hardsetup_card(card, &carrier_ok);
	if (rc) {
		QETH_CARD_TEXT_(card, 2, "2err%04x", rc);
		rc = -ENODEV;
		goto out_remove;
	}

	if (qeth_is_diagass_supported(card, QETH_DIAGS_CMD_TRAP)) {
		if (card->info.hwtrap &&
		    qeth_hw_trap(card, QETH_DIAGS_TRAP_ARM))
			card->info.hwtrap = 0;
	} else
		card->info.hwtrap = 0;

	qeth_bridgeport_query_support(card);
	if (card->options.sbp.supported_funcs)
		dev_info(&card->gdev->dev,
		"The device represents a Bridge Capable Port\n");

	qeth_l2_register_dev_addr(card);

	/* for the rx_bcast characteristic, init VNICC after setmac */
	qeth_l2_vnicc_init(card);

	qeth_trace_features(card);
	qeth_l2_trace_features(card);

	qeth_l2_setup_bridgeport_attrs(card);

	card->state = CARD_STATE_HARDSETUP;
	qeth_print_status_message(card);

	/* softsetup */
	QETH_CARD_TEXT(card, 2, "softsetp");

	if (IS_OSD(card) || IS_OSX(card)) {
		rc = qeth_l2_start_ipassists(card);
		if (rc)
			goto out_remove;
	}

	rc = qeth_init_qdio_queues(card);
	if (rc) {
		QETH_CARD_TEXT_(card, 2, "6err%d", rc);
		rc = -ENODEV;
		goto out_remove;
	}
	card->state = CARD_STATE_SOFTSETUP;

	qeth_set_allowed_threads(card, 0xffffffff, 0);

	if (!qeth_netdev_is_registered(dev)) {
		rc = qeth_l2_setup_netdev(card, carrier_ok);
		if (rc)
			goto out_remove;
	} else {
		rtnl_lock();
		if (carrier_ok)
			netif_carrier_on(dev);
		else
			netif_carrier_off(dev);

		netif_device_attach(dev);
		qeth_enable_hw_features(dev);

		if (card->info.open_when_online) {
			card->info.open_when_online = 0;
			dev_open(dev, NULL);
		}
		rtnl_unlock();
	}
	/* let user_space know that device is online */
	kobject_uevent(&gdev->dev.kobj, KOBJ_CHANGE);
	mutex_unlock(&card->conf_mutex);
	mutex_unlock(&card->discipline_mutex);
	return 0;

out_remove:
	qeth_l2_stop_card(card);
	ccw_device_set_offline(CARD_DDEV(card));
	ccw_device_set_offline(CARD_WDEV(card));
	ccw_device_set_offline(CARD_RDEV(card));
	qdio_free(CARD_DDEV(card));

	mutex_unlock(&card->conf_mutex);
	mutex_unlock(&card->discipline_mutex);
	return rc;
}