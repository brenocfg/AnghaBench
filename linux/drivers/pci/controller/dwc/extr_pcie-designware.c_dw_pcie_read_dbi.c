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
typedef  scalar_t__ u32 ;
struct dw_pcie {int /*<<< orphan*/  dev; scalar_t__ dbi_base; TYPE_1__* ops; } ;
struct TYPE_2__ {scalar_t__ (* read_dbi ) (struct dw_pcie*,scalar_t__,scalar_t__,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dw_pcie_read (scalar_t__,size_t,scalar_t__*) ; 
 scalar_t__ stub1 (struct dw_pcie*,scalar_t__,scalar_t__,size_t) ; 

u32 dw_pcie_read_dbi(struct dw_pcie *pci, u32 reg, size_t size)
{
	int ret;
	u32 val;

	if (pci->ops->read_dbi)
		return pci->ops->read_dbi(pci, pci->dbi_base, reg, size);

	ret = dw_pcie_read(pci->dbi_base + reg, size, &val);
	if (ret)
		dev_err(pci->dev, "Read DBI address failed\n");

	return val;
}