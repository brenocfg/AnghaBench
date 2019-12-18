#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct qed_slowpath_params {int dp_level; int is_vf; int recov_in_prog; int /*<<< orphan*/  name; int /*<<< orphan*/  drv_eng; int /*<<< orphan*/  drv_rev; int /*<<< orphan*/  drv_minor; int /*<<< orphan*/  drv_major; int /*<<< orphan*/  int_mode; int /*<<< orphan*/  dp_module; int /*<<< orphan*/  protocol; } ;
struct qede_dev {TYPE_4__* ndev; int /*<<< orphan*/  rx_copybreak; TYPE_2__* ops; int /*<<< orphan*/  qede_lock; int /*<<< orphan*/  sp_task; int /*<<< orphan*/  flags; int /*<<< orphan*/  dev_info; struct qed_slowpath_params stats; struct qed_dev* cdev; } ;
struct qed_probe_params {int dp_level; int is_vf; int recov_in_prog; int /*<<< orphan*/  name; int /*<<< orphan*/  drv_eng; int /*<<< orphan*/  drv_rev; int /*<<< orphan*/  drv_minor; int /*<<< orphan*/  drv_major; int /*<<< orphan*/  int_mode; int /*<<< orphan*/  dp_module; int /*<<< orphan*/  protocol; } ;
struct qed_dev_eth_info {int dummy; } ;
struct qed_dev {int dummy; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  sp_params ;
typedef  int /*<<< orphan*/  probe_params ;
typedef  enum qede_probe_mode { ____Placeholder_qede_probe_mode } qede_probe_mode ;
typedef  int /*<<< orphan*/  dev_info ;
struct TYPE_12__ {int (* fill_dev_info ) (struct qed_dev*,struct qed_dev_eth_info*) ;TYPE_3__* common; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int (* slowpath_start ) (struct qed_dev*,struct qed_slowpath_params*) ;int /*<<< orphan*/  (* remove ) (struct qed_dev*) ;int /*<<< orphan*/  (* slowpath_stop ) (struct qed_dev*) ;struct qed_dev* (* probe ) (struct pci_dev*,struct qed_slowpath_params*) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  (* register_ops ) (struct qed_dev*,int /*<<< orphan*/ *,struct qede_dev*) ;TYPE_1__* common; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* set_name ) (struct qed_dev*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qede_dev*,char*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_VF (struct qede_dev*) ; 
 int /*<<< orphan*/  QEDE_ENGINEERING_VERSION ; 
 int /*<<< orphan*/  QEDE_FLAGS_IS_VF ; 
 int /*<<< orphan*/  QEDE_MAJOR_VERSION ; 
 int /*<<< orphan*/  QEDE_MINOR_VERSION ; 
 int QEDE_PROBE_NORMAL ; 
 int QEDE_PROBE_RECOVERY ; 
 int /*<<< orphan*/  QEDE_REVISION_VERSION ; 
 int /*<<< orphan*/  QEDE_RX_HDR_SIZE ; 
 int /*<<< orphan*/  QED_DRV_VER_STR_SIZE ; 
 int /*<<< orphan*/  QED_INT_MODE_MSIX ; 
 int QED_LEVEL_INFO ; 
 int /*<<< orphan*/  QED_PROTOCOL_ETH ; 
 int /*<<< orphan*/  free_netdev (TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct qed_dev_eth_info*,int) ; 
 int /*<<< orphan*/  memset (struct qed_slowpath_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_notice (char*) ; 
 TYPE_6__* qed_ops ; 
 struct qede_dev* qede_alloc_etherdev (struct qed_dev*,struct pci_dev*,struct qed_dev_eth_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qede_init_ndev (struct qede_dev*) ; 
 int /*<<< orphan*/  qede_ll_ops ; 
 int /*<<< orphan*/  qede_log_probe (struct qede_dev*) ; 
 int /*<<< orphan*/  qede_ptp_enable (struct qede_dev*,int) ; 
 int qede_rdma_dev_add (struct qede_dev*,int) ; 
 int /*<<< orphan*/  qede_rdma_dev_remove (struct qede_dev*,int) ; 
 int /*<<< orphan*/  qede_set_dcbnl_ops (TYPE_4__*) ; 
 int /*<<< orphan*/  qede_sp_task ; 
 int /*<<< orphan*/  qede_update_pf_params (struct qed_dev*) ; 
 int register_netdev (TYPE_4__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct qed_dev* stub1 (struct pci_dev*,struct qed_slowpath_params*) ; 
 int stub2 (struct qed_dev*,struct qed_slowpath_params*) ; 
 int stub3 (struct qed_dev*,struct qed_dev_eth_info*) ; 
 int /*<<< orphan*/  stub4 (struct qed_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct qed_dev*,int /*<<< orphan*/ *,struct qede_dev*) ; 
 int /*<<< orphan*/  stub6 (struct qed_dev*) ; 
 int /*<<< orphan*/  stub7 (struct qed_dev*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int __qede_probe(struct pci_dev *pdev, u32 dp_module, u8 dp_level,
			bool is_vf, enum qede_probe_mode mode)
{
	struct qed_probe_params probe_params;
	struct qed_slowpath_params sp_params;
	struct qed_dev_eth_info dev_info;
	struct qede_dev *edev;
	struct qed_dev *cdev;
	int rc;

	if (unlikely(dp_level & QED_LEVEL_INFO))
		pr_notice("Starting qede probe\n");

	memset(&probe_params, 0, sizeof(probe_params));
	probe_params.protocol = QED_PROTOCOL_ETH;
	probe_params.dp_module = dp_module;
	probe_params.dp_level = dp_level;
	probe_params.is_vf = is_vf;
	probe_params.recov_in_prog = (mode == QEDE_PROBE_RECOVERY);
	cdev = qed_ops->common->probe(pdev, &probe_params);
	if (!cdev) {
		rc = -ENODEV;
		goto err0;
	}

	qede_update_pf_params(cdev);

	/* Start the Slowpath-process */
	memset(&sp_params, 0, sizeof(sp_params));
	sp_params.int_mode = QED_INT_MODE_MSIX;
	sp_params.drv_major = QEDE_MAJOR_VERSION;
	sp_params.drv_minor = QEDE_MINOR_VERSION;
	sp_params.drv_rev = QEDE_REVISION_VERSION;
	sp_params.drv_eng = QEDE_ENGINEERING_VERSION;
	strlcpy(sp_params.name, "qede LAN", QED_DRV_VER_STR_SIZE);
	rc = qed_ops->common->slowpath_start(cdev, &sp_params);
	if (rc) {
		pr_notice("Cannot start slowpath\n");
		goto err1;
	}

	/* Learn information crucial for qede to progress */
	rc = qed_ops->fill_dev_info(cdev, &dev_info);
	if (rc)
		goto err2;

	if (mode != QEDE_PROBE_RECOVERY) {
		edev = qede_alloc_etherdev(cdev, pdev, &dev_info, dp_module,
					   dp_level);
		if (!edev) {
			rc = -ENOMEM;
			goto err2;
		}
	} else {
		struct net_device *ndev = pci_get_drvdata(pdev);

		edev = netdev_priv(ndev);
		edev->cdev = cdev;
		memset(&edev->stats, 0, sizeof(edev->stats));
		memcpy(&edev->dev_info, &dev_info, sizeof(dev_info));
	}

	if (is_vf)
		set_bit(QEDE_FLAGS_IS_VF, &edev->flags);

	qede_init_ndev(edev);

	rc = qede_rdma_dev_add(edev, (mode == QEDE_PROBE_RECOVERY));
	if (rc)
		goto err3;

	if (mode != QEDE_PROBE_RECOVERY) {
		/* Prepare the lock prior to the registration of the netdev,
		 * as once it's registered we might reach flows requiring it
		 * [it's even possible to reach a flow needing it directly
		 * from there, although it's unlikely].
		 */
		INIT_DELAYED_WORK(&edev->sp_task, qede_sp_task);
		mutex_init(&edev->qede_lock);

		rc = register_netdev(edev->ndev);
		if (rc) {
			DP_NOTICE(edev, "Cannot register net-device\n");
			goto err4;
		}
	}

	edev->ops->common->set_name(cdev, edev->ndev->name);

	/* PTP not supported on VFs */
	if (!is_vf)
		qede_ptp_enable(edev, (mode == QEDE_PROBE_NORMAL));

	edev->ops->register_ops(cdev, &qede_ll_ops, edev);

#ifdef CONFIG_DCB
	if (!IS_VF(edev))
		qede_set_dcbnl_ops(edev->ndev);
#endif

	edev->rx_copybreak = QEDE_RX_HDR_SIZE;

	qede_log_probe(edev);
	return 0;

err4:
	qede_rdma_dev_remove(edev, (mode == QEDE_PROBE_RECOVERY));
err3:
	free_netdev(edev->ndev);
err2:
	qed_ops->common->slowpath_stop(cdev);
err1:
	qed_ops->common->remove(cdev);
err0:
	return rc;
}