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
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  flags; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  dev_port; struct lcs_card* ml_priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  ccwdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  ccwdev; } ;
struct lcs_card {int state; int lan_type; int ip_assists_supported; TYPE_2__ read; TYPE_1__ write; struct net_device* dev; int /*<<< orphan*/  mac; int /*<<< orphan*/  portno; int /*<<< orphan*/  lan_type_trans; } ;
struct ccwgroup_device {int /*<<< orphan*/  dev; int /*<<< orphan*/ * cdev; } ;
typedef  enum lcs_dev_states { ____Placeholder_lcs_dev_states } lcs_dev_states ;

/* Variables and functions */
 int DEV_STATE_RECOVER ; 
 int DEV_STATE_UP ; 
 int ENODEV ; 
 int /*<<< orphan*/  IFF_UP ; 
 int /*<<< orphan*/  LCS_DBF_HEX (int,int /*<<< orphan*/ ,struct lcs_card**,int) ; 
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
#define  LCS_FRAME_TYPE_ENET 129 
#define  LCS_FRAME_TYPE_FDDI 128 
 int LCS_IPASS_IPV6_SUPPORT ; 
 int LCS_IPASS_MULTICAST_SUPPORT ; 
 int /*<<< orphan*/  LCS_MAC_LENGTH ; 
 struct net_device* alloc_etherdev (int /*<<< orphan*/ ) ; 
 struct net_device* alloc_fddidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_device_set_offline (int /*<<< orphan*/ ) ; 
 int ccw_device_set_online (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 struct lcs_card* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eth_type_trans ; 
 int /*<<< orphan*/  fddi_type_trans ; 
 int /*<<< orphan*/  lcs_check_multicast_support (struct lcs_card*) ; 
 int lcs_detect (struct lcs_card*) ; 
 int /*<<< orphan*/  lcs_mc_netdev_ops ; 
 int /*<<< orphan*/  lcs_netdev_ops ; 
 scalar_t__ lcs_register_netdev (struct ccwgroup_device*) ; 
 int /*<<< orphan*/  lcs_set_allowed_threads (struct lcs_card*,int) ; 
 int /*<<< orphan*/  lcs_set_multicast_list (struct net_device*) ; 
 int /*<<< orphan*/  lcs_setup_card (struct lcs_card*) ; 
 int /*<<< orphan*/  lcs_stopcard (struct lcs_card*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setup ; 

__attribute__((used)) static int
lcs_new_device(struct ccwgroup_device *ccwgdev)
{
	struct  lcs_card *card;
	struct net_device *dev=NULL;
	enum lcs_dev_states recover_state;
	int rc;

	card = dev_get_drvdata(&ccwgdev->dev);
	if (!card)
		return -ENODEV;

	LCS_DBF_TEXT(2, setup, "newdev");
	LCS_DBF_HEX(3, setup, &card, sizeof(void*));
	card->read.ccwdev  = ccwgdev->cdev[0];
	card->write.ccwdev = ccwgdev->cdev[1];

	recover_state = card->state;
	rc = ccw_device_set_online(card->read.ccwdev);
	if (rc)
		goto out_err;
	rc = ccw_device_set_online(card->write.ccwdev);
	if (rc)
		goto out_werr;

	LCS_DBF_TEXT(3, setup, "lcsnewdv");

	lcs_setup_card(card);
	rc = lcs_detect(card);
	if (rc) {
		LCS_DBF_TEXT(2, setup, "dtctfail");
		dev_err(&ccwgdev->dev,
			"Detecting a network adapter for LCS devices"
			" failed with rc=%d (0x%x)\n", rc, rc);
		lcs_stopcard(card);
		goto out;
	}
	if (card->dev) {
		LCS_DBF_TEXT(2, setup, "samedev");
		LCS_DBF_HEX(3, setup, &card, sizeof(void*));
		goto netdev_out;
	}
	switch (card->lan_type) {
#ifdef CONFIG_ETHERNET
	case LCS_FRAME_TYPE_ENET:
		card->lan_type_trans = eth_type_trans;
		dev = alloc_etherdev(0);
		break;
#endif
#ifdef CONFIG_FDDI
	case LCS_FRAME_TYPE_FDDI:
		card->lan_type_trans = fddi_type_trans;
		dev = alloc_fddidev(0);
		break;
#endif
	default:
		LCS_DBF_TEXT(3, setup, "errinit");
		pr_err(" Initialization failed\n");
		goto out;
	}
	if (!dev)
		goto out;
	card->dev = dev;
	card->dev->ml_priv = card;
	card->dev->netdev_ops = &lcs_netdev_ops;
	card->dev->dev_port = card->portno;
	memcpy(card->dev->dev_addr, card->mac, LCS_MAC_LENGTH);
#ifdef CONFIG_IP_MULTICAST
	if (!lcs_check_multicast_support(card))
		card->dev->netdev_ops = &lcs_mc_netdev_ops;
#endif
netdev_out:
	lcs_set_allowed_threads(card,0xffffffff);
	if (recover_state == DEV_STATE_RECOVER) {
		lcs_set_multicast_list(card->dev);
		card->dev->flags |= IFF_UP;
		netif_carrier_on(card->dev);
		netif_wake_queue(card->dev);
		card->state = DEV_STATE_UP;
	} else {
		lcs_stopcard(card);
	}

	if (lcs_register_netdev(ccwgdev) != 0)
		goto out;

	/* Print out supported assists: IPv6 */
	pr_info("LCS device %s %s IPv6 support\n", card->dev->name,
		(card->ip_assists_supported & LCS_IPASS_IPV6_SUPPORT) ?
		"with" : "without");
	/* Print out supported assist: Multicast */
	pr_info("LCS device %s %s Multicast support\n", card->dev->name,
		(card->ip_assists_supported & LCS_IPASS_MULTICAST_SUPPORT) ?
		"with" : "without");
	return 0;
out:

	ccw_device_set_offline(card->write.ccwdev);
out_werr:
	ccw_device_set_offline(card->read.ccwdev);
out_err:
	return -ENODEV;
}