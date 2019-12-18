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
typedef  unsigned int u32 ;
struct rcar_pcie {int dummy; } ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 unsigned int rcar_pci_read_reg (struct rcar_pcie*,int) ; 
 int /*<<< orphan*/  rcar_pci_write_reg (struct rcar_pcie*,unsigned int,int) ; 

__attribute__((used)) static void rcar_rmw32(struct rcar_pcie *pcie, int where, u32 mask, u32 data)
{
	unsigned int shift = BITS_PER_BYTE * (where & 3);
	u32 val = rcar_pci_read_reg(pcie, where & ~3);

	val &= ~(mask << shift);
	val |= data << shift;
	rcar_pci_write_reg(pcie, val, where & ~3);
}