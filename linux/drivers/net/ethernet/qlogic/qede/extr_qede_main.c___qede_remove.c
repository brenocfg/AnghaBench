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
struct qede_dev {TYPE_2__* ops; int /*<<< orphan*/  sp_task; struct qed_dev* cdev; } ;
struct qed_dev {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
typedef  enum qede_remove_mode { ____Placeholder_qede_remove_mode } qede_remove_mode ;
struct TYPE_8__ {TYPE_3__* common; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* remove ) (struct qed_dev*) ;int /*<<< orphan*/  (* slowpath_stop ) (struct qed_dev*) ;} ;
struct TYPE_6__ {TYPE_1__* common; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_power_state ) (struct qed_dev*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qede_dev*,char*) ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int QEDE_REMOVE_RECOVERY ; 
 scalar_t__ SYSTEM_POWER_OFF ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 TYPE_4__* qed_ops ; 
 int /*<<< orphan*/  qede_ptp_disable (struct qede_dev*) ; 
 int /*<<< orphan*/  qede_rdma_dev_remove (struct qede_dev*,int) ; 
 int /*<<< orphan*/  stub1 (struct qed_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct qed_dev*) ; 
 int /*<<< orphan*/  stub3 (struct qed_dev*) ; 
 scalar_t__ system_state ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void __qede_remove(struct pci_dev *pdev, enum qede_remove_mode mode)
{
	struct net_device *ndev = pci_get_drvdata(pdev);
	struct qede_dev *edev;
	struct qed_dev *cdev;

	if (!ndev) {
		dev_info(&pdev->dev, "Device has already been removed\n");
		return;
	}

	edev = netdev_priv(ndev);
	cdev = edev->cdev;

	DP_INFO(edev, "Starting qede_remove\n");

	qede_rdma_dev_remove(edev, (mode == QEDE_REMOVE_RECOVERY));

	if (mode != QEDE_REMOVE_RECOVERY) {
		unregister_netdev(ndev);

		cancel_delayed_work_sync(&edev->sp_task);

		edev->ops->common->set_power_state(cdev, PCI_D0);

		pci_set_drvdata(pdev, NULL);
	}

	qede_ptp_disable(edev);

	/* Use global ops since we've freed edev */
	qed_ops->common->slowpath_stop(cdev);
	if (system_state == SYSTEM_POWER_OFF)
		return;
	qed_ops->common->remove(cdev);

	/* Since this can happen out-of-sync with other flows,
	 * don't release the netdevice until after slowpath stop
	 * has been called to guarantee various other contexts
	 * [e.g., QED register callbacks] won't break anything when
	 * accessing the netdevice.
	 */
	if (mode != QEDE_REMOVE_RECOVERY)
		free_netdev(ndev);

	dev_info(&pdev->dev, "Ending qede_remove successfully\n");
}