#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qed_probe_params {int /*<<< orphan*/  recov_in_prog; int /*<<< orphan*/  dp_level; int /*<<< orphan*/  dp_module; scalar_t__ is_vf; int /*<<< orphan*/  protocol; } ;
struct qed_dev {int b_is_vf; int /*<<< orphan*/  recov_in_prog; int /*<<< orphan*/  protocol; int /*<<< orphan*/  drv_type; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_dev*,char*) ; 
 int /*<<< orphan*/  DP_INFO (struct qed_dev*,char*) ; 
 int /*<<< orphan*/  DRV_ID_DRV_TYPE_LINUX ; 
 int /*<<< orphan*/  QED_PCI_DEFAULT ; 
 struct qed_dev* qed_alloc_cdev (struct pci_dev*) ; 
 int qed_devlink_register (struct qed_dev*) ; 
 int /*<<< orphan*/  qed_free_cdev (struct qed_dev*) ; 
 int /*<<< orphan*/  qed_free_pci (struct qed_dev*) ; 
 int qed_hw_prepare (struct qed_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_init_dp (struct qed_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qed_init_pci (struct qed_dev*,struct pci_dev*) ; 

__attribute__((used)) static struct qed_dev *qed_probe(struct pci_dev *pdev,
				 struct qed_probe_params *params)
{
	struct qed_dev *cdev;
	int rc;

	cdev = qed_alloc_cdev(pdev);
	if (!cdev)
		goto err0;

	cdev->drv_type = DRV_ID_DRV_TYPE_LINUX;
	cdev->protocol = params->protocol;

	if (params->is_vf)
		cdev->b_is_vf = true;

	qed_init_dp(cdev, params->dp_module, params->dp_level);

	cdev->recov_in_prog = params->recov_in_prog;

	rc = qed_init_pci(cdev, pdev);
	if (rc) {
		DP_ERR(cdev, "init pci failed\n");
		goto err1;
	}
	DP_INFO(cdev, "PCI init completed successfully\n");

	rc = qed_devlink_register(cdev);
	if (rc) {
		DP_INFO(cdev, "Failed to register devlink.\n");
		goto err2;
	}

	rc = qed_hw_prepare(cdev, QED_PCI_DEFAULT);
	if (rc) {
		DP_ERR(cdev, "hw prepare failed\n");
		goto err2;
	}

	DP_INFO(cdev, "qed_probe completed successfully\n");

	return cdev;

err2:
	qed_free_pci(cdev);
err1:
	qed_free_cdev(cdev);
err0:
	return NULL;
}