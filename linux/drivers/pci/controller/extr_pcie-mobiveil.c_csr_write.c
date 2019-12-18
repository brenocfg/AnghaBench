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
struct mobiveil_pcie {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* mobiveil_pcie_comp_addr (struct mobiveil_pcie*,int /*<<< orphan*/ ) ; 
 int mobiveil_pcie_write (void*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void csr_write(struct mobiveil_pcie *pcie, u32 val, u32 off, size_t size)
{
	void *addr;
	int ret;

	addr = mobiveil_pcie_comp_addr(pcie, off);

	ret = mobiveil_pcie_write(addr, size, val);
	if (ret)
		dev_err(&pcie->pdev->dev, "write CSR address failed\n");
}