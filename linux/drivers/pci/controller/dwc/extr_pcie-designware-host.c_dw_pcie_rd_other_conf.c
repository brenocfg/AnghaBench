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
typedef  int /*<<< orphan*/  u32 ;
struct pcie_port {TYPE_1__* ops; } ;
struct pci_bus {int dummy; } ;
struct TYPE_2__ {int (* rd_other_conf ) (struct pcie_port*,struct pci_bus*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int dw_pcie_access_other_conf (struct pcie_port*,struct pci_bus*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int) ; 
 int stub1 (struct pcie_port*,struct pci_bus*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dw_pcie_rd_other_conf(struct pcie_port *pp, struct pci_bus *bus,
				 u32 devfn, int where, int size, u32 *val)
{
	if (pp->ops->rd_other_conf)
		return pp->ops->rd_other_conf(pp, bus, devfn, where,
					      size, val);

	return dw_pcie_access_other_conf(pp, bus, devfn, where, size, val,
					 false);
}