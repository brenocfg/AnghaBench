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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {scalar_t__ wol_support; } ;
struct TYPE_4__ {TYPE_1__ common; } ;
struct qede_dev {int wol_enabled; int /*<<< orphan*/  vlan_list; TYPE_2__ dev_info; int /*<<< orphan*/  stats; int /*<<< orphan*/  q_num_tx_buffers; int /*<<< orphan*/  q_num_rx_buffers; int /*<<< orphan*/  ops; int /*<<< orphan*/  dp_level; int /*<<< orphan*/  dp_module; struct pci_dev* pdev; struct qed_dev* cdev; struct net_device* ndev; } ;
struct qed_dev_eth_info {int num_queues; int num_tc; } ;
struct qed_dev {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qede_dev*,char*,int,int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NUM_RX_BDS_DEF ; 
 int /*<<< orphan*/  NUM_TX_BDS_DEF ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_etherdev_mqs (int,int,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,struct qed_dev_eth_info*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  qed_ops ; 

__attribute__((used)) static struct qede_dev *qede_alloc_etherdev(struct qed_dev *cdev,
					    struct pci_dev *pdev,
					    struct qed_dev_eth_info *info,
					    u32 dp_module, u8 dp_level)
{
	struct net_device *ndev;
	struct qede_dev *edev;

	ndev = alloc_etherdev_mqs(sizeof(*edev),
				  info->num_queues * info->num_tc,
				  info->num_queues);
	if (!ndev) {
		pr_err("etherdev allocation failed\n");
		return NULL;
	}

	edev = netdev_priv(ndev);
	edev->ndev = ndev;
	edev->cdev = cdev;
	edev->pdev = pdev;
	edev->dp_module = dp_module;
	edev->dp_level = dp_level;
	edev->ops = qed_ops;
	edev->q_num_rx_buffers = NUM_RX_BDS_DEF;
	edev->q_num_tx_buffers = NUM_TX_BDS_DEF;

	DP_INFO(edev, "Allocated netdev with %d tx queues and %d rx queues\n",
		info->num_queues, info->num_queues);

	SET_NETDEV_DEV(ndev, &pdev->dev);

	memset(&edev->stats, 0, sizeof(edev->stats));
	memcpy(&edev->dev_info, info, sizeof(*info));

	/* As ethtool doesn't have the ability to show WoL behavior as
	 * 'default', if device supports it declare it's enabled.
	 */
	if (edev->dev_info.common.wol_support)
		edev->wol_enabled = true;

	INIT_LIST_HEAD(&edev->vlan_list);

	return edev;
}