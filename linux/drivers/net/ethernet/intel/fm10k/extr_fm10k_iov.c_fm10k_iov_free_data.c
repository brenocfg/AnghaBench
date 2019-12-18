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
struct pci_dev {int dummy; } ;
struct fm10k_intfc {int /*<<< orphan*/ * iov_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  fm10k_iov_suspend (struct pci_dev*) ; 
 int /*<<< orphan*/  kfree_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct fm10k_intfc* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  rcu ; 

__attribute__((used)) static void fm10k_iov_free_data(struct pci_dev *pdev)
{
	struct fm10k_intfc *interface = pci_get_drvdata(pdev);

	if (!interface->iov_data)
		return;

	/* reclaim hardware resources */
	fm10k_iov_suspend(pdev);

	/* drop iov_data from interface */
	kfree_rcu(interface->iov_data, rcu);
	interface->iov_data = NULL;
}