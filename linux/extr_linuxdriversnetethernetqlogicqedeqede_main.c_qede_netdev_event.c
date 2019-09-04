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
struct qede_dev {TYPE_4__* ndev; int /*<<< orphan*/  cdev; TYPE_3__* ops; } ;
struct notifier_block {int dummy; } ;
struct net_device {TYPE_1__* ethtool_ops; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  driver; } ;
typedef  int /*<<< orphan*/  drvinfo ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_2__* common; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_name ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_drvinfo ) (struct net_device*,struct ethtool_drvinfo*) ;} ;

/* Variables and functions */
#define  NETDEV_CHANGEADDR 129 
#define  NETDEV_CHANGENAME 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  memset (struct ethtool_drvinfo*,int /*<<< orphan*/ ,int) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  qede_rdma_event_changeaddr (struct qede_dev*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,struct ethtool_drvinfo*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qede_netdev_event(struct notifier_block *this, unsigned long event,
			     void *ptr)
{
	struct net_device *ndev = netdev_notifier_info_to_dev(ptr);
	struct ethtool_drvinfo drvinfo;
	struct qede_dev *edev;

	if (event != NETDEV_CHANGENAME && event != NETDEV_CHANGEADDR)
		goto done;

	/* Check whether this is a qede device */
	if (!ndev || !ndev->ethtool_ops || !ndev->ethtool_ops->get_drvinfo)
		goto done;

	memset(&drvinfo, 0, sizeof(drvinfo));
	ndev->ethtool_ops->get_drvinfo(ndev, &drvinfo);
	if (strcmp(drvinfo.driver, "qede"))
		goto done;
	edev = netdev_priv(ndev);

	switch (event) {
	case NETDEV_CHANGENAME:
		/* Notify qed of the name change */
		if (!edev->ops || !edev->ops->common)
			goto done;
		edev->ops->common->set_name(edev->cdev, edev->ndev->name);
		break;
	case NETDEV_CHANGEADDR:
		edev = netdev_priv(ndev);
		qede_rdma_event_changeaddr(edev);
		break;
	}

done:
	return NOTIFY_DONE;
}