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
typedef  int /*<<< orphan*/  pci_ers_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 scalar_t__ qlcnic_attach_func (struct pci_dev*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static pci_ers_result_t qlcnic_82xx_io_slot_reset(struct pci_dev *pdev)
{
	pci_ers_result_t res;

	rtnl_lock();
	res = qlcnic_attach_func(pdev) ? PCI_ERS_RESULT_DISCONNECT :
					 PCI_ERS_RESULT_RECOVERED;
	rtnl_unlock();

	return res;
}