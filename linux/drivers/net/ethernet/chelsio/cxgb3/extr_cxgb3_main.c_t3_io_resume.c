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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_PCIE_PEX_ERR ; 
 int /*<<< orphan*/  CH_ALERT (struct adapter*,char*,int /*<<< orphan*/ ) ; 
 struct adapter* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  t3_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_resume_ports (struct adapter*) ; 

__attribute__((used)) static void t3_io_resume(struct pci_dev *pdev)
{
	struct adapter *adapter = pci_get_drvdata(pdev);

	CH_ALERT(adapter, "adapter recovering, PEX ERR 0x%x\n",
		 t3_read_reg(adapter, A_PCIE_PEX_ERR));

	rtnl_lock();
	t3_resume_ports(adapter);
	rtnl_unlock();
}