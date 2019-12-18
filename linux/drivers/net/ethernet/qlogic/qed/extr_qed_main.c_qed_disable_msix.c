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
struct qed_int_param {int dummy; } ;
struct TYPE_4__ {scalar_t__ int_mode; } ;
struct TYPE_3__ {TYPE_2__ out; int /*<<< orphan*/  msix_table; } ;
struct qed_dev {TYPE_1__ int_params; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ QED_INT_MODE_MSI ; 
 scalar_t__ QED_INT_MODE_MSIX ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_disable_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_msix (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_disable_msix(struct qed_dev *cdev)
{
	if (cdev->int_params.out.int_mode == QED_INT_MODE_MSIX) {
		pci_disable_msix(cdev->pdev);
		kfree(cdev->int_params.msix_table);
	} else if (cdev->int_params.out.int_mode == QED_INT_MODE_MSI) {
		pci_disable_msi(cdev->pdev);
	}

	memset(&cdev->int_params.out, 0, sizeof(struct qed_int_param));
}