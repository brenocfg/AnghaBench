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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct qede_dev {scalar_t__ state; int /*<<< orphan*/  cdev; TYPE_2__* ops; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_4__ {TYPE_1__* common; int /*<<< orphan*/  (* req_bulletin_update_mac ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* check_mac ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* update_mac ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qede_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qede_dev*,char*,...) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qede_dev*,int /*<<< orphan*/ ,char*) ; 
 int EFAULT ; 
 int EINVAL ; 
 scalar_t__ IS_VF (struct qede_dev*) ; 
 int /*<<< orphan*/  NETIF_MSG_IFDOWN ; 
 scalar_t__ QEDE_STATE_OPEN ; 
 int /*<<< orphan*/  QED_FILTER_XCAST_TYPE_ADD ; 
 int /*<<< orphan*/  QED_FILTER_XCAST_TYPE_DEL ; 
 int /*<<< orphan*/  __qede_lock (struct qede_dev*) ; 
 int /*<<< orphan*/  __qede_unlock (struct qede_dev*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int qede_set_ucast_rx_mac (struct qede_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int qede_set_mac_addr(struct net_device *ndev, void *p)
{
	struct qede_dev *edev = netdev_priv(ndev);
	struct sockaddr *addr = p;
	int rc = 0;

	/* Make sure the state doesn't transition while changing the MAC.
	 * Also, all flows accessing the dev_addr field are doing that under
	 * this lock.
	 */
	__qede_lock(edev);

	if (!is_valid_ether_addr(addr->sa_data)) {
		DP_NOTICE(edev, "The MAC address is not valid\n");
		rc = -EFAULT;
		goto out;
	}

	if (!edev->ops->check_mac(edev->cdev, addr->sa_data)) {
		DP_NOTICE(edev, "qed prevents setting MAC %pM\n",
			  addr->sa_data);
		rc = -EINVAL;
		goto out;
	}

	if (edev->state == QEDE_STATE_OPEN) {
		/* Remove the previous primary mac */
		rc = qede_set_ucast_rx_mac(edev, QED_FILTER_XCAST_TYPE_DEL,
					   ndev->dev_addr);
		if (rc)
			goto out;
	}

	ether_addr_copy(ndev->dev_addr, addr->sa_data);
	DP_INFO(edev, "Setting device MAC to %pM\n", addr->sa_data);

	if (edev->state != QEDE_STATE_OPEN) {
		DP_VERBOSE(edev, NETIF_MSG_IFDOWN,
			   "The device is currently down\n");
		/* Ask PF to explicitly update a copy in bulletin board */
		if (IS_VF(edev) && edev->ops->req_bulletin_update_mac)
			edev->ops->req_bulletin_update_mac(edev->cdev,
							   ndev->dev_addr);
		goto out;
	}

	edev->ops->common->update_mac(edev->cdev, ndev->dev_addr);

	rc = qede_set_ucast_rx_mac(edev, QED_FILTER_XCAST_TYPE_ADD,
				   ndev->dev_addr);
out:
	__qede_unlock(edev);
	return rc;
}