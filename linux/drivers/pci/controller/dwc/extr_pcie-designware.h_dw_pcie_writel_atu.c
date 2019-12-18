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
typedef  int /*<<< orphan*/  u32 ;
struct dw_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dw_pcie_write_atu (struct dw_pcie*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dw_pcie_writel_atu(struct dw_pcie *pci, u32 reg, u32 val)
{
	dw_pcie_write_atu(pci, reg, 0x4, val);
}