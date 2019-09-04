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

/* Variables and functions */
 int /*<<< orphan*/  __mthca_remove_one (struct pci_dev*) ; 
 int /*<<< orphan*/  mthca_device_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mthca_remove_one(struct pci_dev *pdev)
{
	mutex_lock(&mthca_device_mutex);
	__mthca_remove_one(pdev);
	mutex_unlock(&mthca_device_mutex);
}