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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct qedr_dev {TYPE_4__ ibdev; int /*<<< orphan*/  enet_state; int /*<<< orphan*/  wq_multiplier; int /*<<< orphan*/  num_cnq; TYPE_2__* ops; int /*<<< orphan*/  rdma_ctx; int /*<<< orphan*/  num_hwfns; int /*<<< orphan*/  rdma_type; int /*<<< orphan*/  user_dpm_enabled; struct qed_dev* cdev; struct net_device* ndev; struct pci_dev* pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  num_hwfns; } ;
struct qed_dev_rdma_info {TYPE_1__ common; int /*<<< orphan*/  rdma_type; int /*<<< orphan*/  user_dpm_enabled; } ;
struct qed_dev {int dummy; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_7__ {int (* fill_dev_info ) (struct qed_dev*,struct qed_dev_rdma_info*) ;int /*<<< orphan*/  (* rdma_get_min_cnq_msix ) (struct qed_dev*) ;int /*<<< orphan*/  (* rdma_get_rdma_ctx ) (struct qed_dev*) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DP_DEBUG (struct qedr_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,...) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IB_EVENT_PORT_ACTIVE ; 
 int /*<<< orphan*/  QEDR_ENET_STATE_BIT ; 
 int /*<<< orphan*/  QEDR_MSG_INIT ; 
 int /*<<< orphan*/  QEDR_PORT ; 
 int /*<<< orphan*/  QEDR_WQ_MULTIPLIER_DFT ; 
 scalar_t__ device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_alloc_device (int) ; 
 int /*<<< orphan*/  ib_dealloc_device (TYPE_4__*) ; 
 int /*<<< orphan*/  ib_unregister_device (TYPE_4__*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 TYPE_2__* qed_get_rdma_ops () ; 
 TYPE_2__* qed_ops ; 
 int qedr_alloc_resources (struct qedr_dev*) ; 
 int /*<<< orphan*/ * qedr_attributes ; 
 int /*<<< orphan*/  qedr_free_resources (struct qedr_dev*) ; 
 int /*<<< orphan*/  qedr_ib_dispatch_event (struct qedr_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qedr_init_hw (struct qedr_dev*) ; 
 int /*<<< orphan*/  qedr_pci_set_atomic (struct qedr_dev*,struct pci_dev*) ; 
 int qedr_register_device (struct qedr_dev*) ; 
 int qedr_setup_irqs (struct qedr_dev*) ; 
 int /*<<< orphan*/  qedr_stop_hw (struct qedr_dev*) ; 
 int /*<<< orphan*/  qedr_sync_free_irqs (struct qedr_dev*) ; 
 int stub1 (struct qed_dev*,struct qed_dev_rdma_info*) ; 
 int /*<<< orphan*/  stub2 (struct qed_dev*) ; 
 int /*<<< orphan*/  stub3 (struct qed_dev*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct qedr_dev *qedr_add(struct qed_dev *cdev, struct pci_dev *pdev,
				 struct net_device *ndev)
{
	struct qed_dev_rdma_info dev_info;
	struct qedr_dev *dev;
	int rc = 0, i;

	dev = (struct qedr_dev *)ib_alloc_device(sizeof(*dev));
	if (!dev) {
		pr_err("Unable to allocate ib device\n");
		return NULL;
	}

	DP_DEBUG(dev, QEDR_MSG_INIT, "qedr add device called\n");

	dev->pdev = pdev;
	dev->ndev = ndev;
	dev->cdev = cdev;

	qed_ops = qed_get_rdma_ops();
	if (!qed_ops) {
		DP_ERR(dev, "Failed to get qed roce operations\n");
		goto init_err;
	}

	dev->ops = qed_ops;
	rc = qed_ops->fill_dev_info(cdev, &dev_info);
	if (rc)
		goto init_err;

	dev->user_dpm_enabled = dev_info.user_dpm_enabled;
	dev->rdma_type = dev_info.rdma_type;
	dev->num_hwfns = dev_info.common.num_hwfns;
	dev->rdma_ctx = dev->ops->rdma_get_rdma_ctx(cdev);

	dev->num_cnq = dev->ops->rdma_get_min_cnq_msix(cdev);
	if (!dev->num_cnq) {
		DP_ERR(dev, "Failed. At least one CNQ is required.\n");
		rc = -ENOMEM;
		goto init_err;
	}

	dev->wq_multiplier = QEDR_WQ_MULTIPLIER_DFT;

	qedr_pci_set_atomic(dev, pdev);

	rc = qedr_alloc_resources(dev);
	if (rc)
		goto init_err;

	rc = qedr_init_hw(dev);
	if (rc)
		goto alloc_err;

	rc = qedr_setup_irqs(dev);
	if (rc)
		goto irq_err;

	rc = qedr_register_device(dev);
	if (rc) {
		DP_ERR(dev, "Unable to allocate register device\n");
		goto reg_err;
	}

	for (i = 0; i < ARRAY_SIZE(qedr_attributes); i++)
		if (device_create_file(&dev->ibdev.dev, qedr_attributes[i]))
			goto sysfs_err;

	if (!test_and_set_bit(QEDR_ENET_STATE_BIT, &dev->enet_state))
		qedr_ib_dispatch_event(dev, QEDR_PORT, IB_EVENT_PORT_ACTIVE);

	DP_DEBUG(dev, QEDR_MSG_INIT, "qedr driver loaded successfully\n");
	return dev;

sysfs_err:
	ib_unregister_device(&dev->ibdev);
reg_err:
	qedr_sync_free_irqs(dev);
irq_err:
	qedr_stop_hw(dev);
alloc_err:
	qedr_free_resources(dev);
init_err:
	ib_dealloc_device(&dev->ibdev);
	DP_ERR(dev, "qedr driver load failed rc=%d\n", rc);

	return NULL;
}