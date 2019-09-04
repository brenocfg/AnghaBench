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
struct TYPE_4__ {int int_mode; } ;
struct TYPE_3__ {int int_mode; int num_vectors; } ;
struct qed_int_params {TYPE_2__ out; TYPE_1__ in; int /*<<< orphan*/  msix_table; } ;
struct qed_dev {int num_hwfns; int /*<<< orphan*/  int_coalescing_mode; int /*<<< orphan*/  pdev; struct qed_int_params int_params; } ;
struct msix_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qed_dev*,char*,char*) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_dev*,char*,...) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QED_COAL_MODE_ENABLE ; 
#define  QED_INT_MODE_INTA 130 
#define  QED_INT_MODE_MSI 129 
#define  QED_INT_MODE_MSIX 128 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int pci_enable_msi (int /*<<< orphan*/ ) ; 
 int qed_enable_msix (struct qed_dev*,struct qed_int_params*) ; 

__attribute__((used)) static int qed_set_int_mode(struct qed_dev *cdev, bool force_mode)
{
	struct qed_int_params *int_params = &cdev->int_params;
	struct msix_entry *tbl;
	int rc = 0, cnt;

	switch (int_params->in.int_mode) {
	case QED_INT_MODE_MSIX:
		/* Allocate MSIX table */
		cnt = int_params->in.num_vectors;
		int_params->msix_table = kcalloc(cnt, sizeof(*tbl), GFP_KERNEL);
		if (!int_params->msix_table) {
			rc = -ENOMEM;
			goto out;
		}

		/* Enable MSIX */
		rc = qed_enable_msix(cdev, int_params);
		if (!rc)
			goto out;

		DP_NOTICE(cdev, "Failed to enable MSI-X\n");
		kfree(int_params->msix_table);
		if (force_mode)
			goto out;
		/* Fallthrough */

	case QED_INT_MODE_MSI:
		if (cdev->num_hwfns == 1) {
			rc = pci_enable_msi(cdev->pdev);
			if (!rc) {
				int_params->out.int_mode = QED_INT_MODE_MSI;
				goto out;
			}

			DP_NOTICE(cdev, "Failed to enable MSI\n");
			if (force_mode)
				goto out;
		}
		/* Fallthrough */

	case QED_INT_MODE_INTA:
			int_params->out.int_mode = QED_INT_MODE_INTA;
			rc = 0;
			goto out;
	default:
		DP_NOTICE(cdev, "Unknown int_mode value %d\n",
			  int_params->in.int_mode);
		rc = -EINVAL;
	}

out:
	if (!rc)
		DP_INFO(cdev, "Using %s interrupts\n",
			int_params->out.int_mode == QED_INT_MODE_INTA ?
			"INTa" : int_params->out.int_mode == QED_INT_MODE_MSI ?
			"MSI" : "MSIX");
	cdev->int_coalescing_mode = QED_COAL_MODE_ENABLE;

	return rc;
}