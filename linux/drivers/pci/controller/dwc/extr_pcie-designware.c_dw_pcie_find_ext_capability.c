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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct dw_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dw_pcie_find_next_ext_capability (struct dw_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u16 dw_pcie_find_ext_capability(struct dw_pcie *pci, u8 cap)
{
	return dw_pcie_find_next_ext_capability(pci, 0, cap);
}