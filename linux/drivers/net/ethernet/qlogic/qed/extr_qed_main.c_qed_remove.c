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
struct qed_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  qed_devlink_unregister (struct qed_dev*) ; 
 int /*<<< orphan*/  qed_free_cdev (struct qed_dev*) ; 
 int /*<<< orphan*/  qed_free_pci (struct qed_dev*) ; 
 int /*<<< orphan*/  qed_hw_remove (struct qed_dev*) ; 
 int /*<<< orphan*/  qed_set_power_state (struct qed_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_remove(struct qed_dev *cdev)
{
	if (!cdev)
		return;

	qed_hw_remove(cdev);

	qed_free_pci(cdev);

	qed_set_power_state(cdev, PCI_D3hot);

	qed_devlink_unregister(cdev);

	qed_free_cdev(cdev);
}