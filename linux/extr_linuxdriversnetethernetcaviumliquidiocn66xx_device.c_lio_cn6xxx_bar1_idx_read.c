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
struct octeon_device {int /*<<< orphan*/  pcie_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN6XXX_BAR1_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_pci_readq (struct octeon_device*,int /*<<< orphan*/ ) ; 

u32 lio_cn6xxx_bar1_idx_read(struct octeon_device *oct, u32 idx)
{
	return (u32)lio_pci_readq(oct, CN6XXX_BAR1_REG(idx, oct->pcie_port));
}