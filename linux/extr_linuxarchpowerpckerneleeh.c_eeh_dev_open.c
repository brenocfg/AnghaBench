#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct eeh_dev {TYPE_1__* pe; } ;
struct TYPE_2__ {int /*<<< orphan*/  pass_dev_cnt; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eeh_dev_mutex ; 
 int eeh_pe_change_owner (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct eeh_dev* pci_dev_to_eeh_dev (struct pci_dev*) ; 

int eeh_dev_open(struct pci_dev *pdev)
{
	struct eeh_dev *edev;
	int ret = -ENODEV;

	mutex_lock(&eeh_dev_mutex);

	/* No PCI device ? */
	if (!pdev)
		goto out;

	/* No EEH device or PE ? */
	edev = pci_dev_to_eeh_dev(pdev);
	if (!edev || !edev->pe)
		goto out;

	/*
	 * The PE might have been put into frozen state, but we
	 * didn't detect that yet. The passed through PCI devices
	 * in frozen PE won't work properly. Clear the frozen state
	 * in advance.
	 */
	ret = eeh_pe_change_owner(edev->pe);
	if (ret)
		goto out;

	/* Increase PE's pass through count */
	atomic_inc(&edev->pe->pass_dev_cnt);
	mutex_unlock(&eeh_dev_mutex);

	return 0;
out:
	mutex_unlock(&eeh_dev_mutex);
	return ret;
}