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
struct qlcnic_adapter {TYPE_1__* nic_ops; } ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int (* shutdown ) (struct pci_dev*) ;} ;

/* Variables and functions */
 struct qlcnic_adapter* pci_get_drvdata (struct pci_dev*) ; 
 int stub1 (struct pci_dev*) ; 

__attribute__((used)) static inline int __qlcnic_shutdown(struct pci_dev *pdev)
{
	struct qlcnic_adapter *adapter = pci_get_drvdata(pdev);

	return adapter->nic_ops->shutdown(pdev);
}