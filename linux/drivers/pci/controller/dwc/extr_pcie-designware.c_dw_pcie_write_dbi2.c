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
struct dw_pcie {int /*<<< orphan*/  dev; scalar_t__ dbi_base2; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_dbi2 ) (struct dw_pcie*,scalar_t__,scalar_t__,size_t,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dw_pcie_write (scalar_t__,size_t,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct dw_pcie*,scalar_t__,scalar_t__,size_t,scalar_t__) ; 

void dw_pcie_write_dbi2(struct dw_pcie *pci, u32 reg, size_t size, u32 val)
{
	int ret;

	if (pci->ops->write_dbi2) {
		pci->ops->write_dbi2(pci, pci->dbi_base2, reg, size, val);
		return;
	}

	ret = dw_pcie_write(pci->dbi_base2 + reg, size, val);
	if (ret)
		dev_err(pci->dev, "write DBI address failed\n");
}