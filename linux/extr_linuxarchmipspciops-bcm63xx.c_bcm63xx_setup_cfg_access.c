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

/* Variables and functions */
 unsigned int MPI_L2PCFG_CFG_SEL_MASK ; 
 int MPI_L2PCFG_CFG_TYPE_SHIFT ; 
 unsigned int MPI_L2PCFG_CFG_USEREG_MASK ; 
 unsigned int MPI_L2PCFG_DEVNUM_MASK ; 
 unsigned int MPI_L2PCFG_DEVNUM_SHIFT ; 
 unsigned int MPI_L2PCFG_FUNC_MASK ; 
 unsigned int MPI_L2PCFG_FUNC_SHIFT ; 
 int /*<<< orphan*/  MPI_L2PCFG_REG ; 
 unsigned int MPI_L2PCFG_REG_MASK ; 
 unsigned int MPI_L2PCFG_REG_SHIFT ; 
 unsigned int PCI_FUNC (unsigned int) ; 
 unsigned int PCI_SLOT (unsigned int) ; 
 int /*<<< orphan*/  bcm_mpi_writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm63xx_setup_cfg_access(int type, unsigned int busn,
				    unsigned int devfn, int where)
{
	unsigned int slot, func, reg;
	u32 val;

	slot = PCI_SLOT(devfn);
	func = PCI_FUNC(devfn);
	reg = where >> 2;

	/* sanity check */
	if (slot > (MPI_L2PCFG_DEVNUM_MASK >> MPI_L2PCFG_DEVNUM_SHIFT))
		return 1;

	if (func > (MPI_L2PCFG_FUNC_MASK >> MPI_L2PCFG_FUNC_SHIFT))
		return 1;

	if (reg > (MPI_L2PCFG_REG_MASK >> MPI_L2PCFG_REG_SHIFT))
		return 1;

	/* ok, setup config access */
	val = (reg << MPI_L2PCFG_REG_SHIFT);
	val |= (func << MPI_L2PCFG_FUNC_SHIFT);
	val |= (slot << MPI_L2PCFG_DEVNUM_SHIFT);
	val |= MPI_L2PCFG_CFG_USEREG_MASK;
	val |= MPI_L2PCFG_CFG_SEL_MASK;
	/* type 0 cycle for local bus, type 1 cycle for anything else */
	if (type != 0) {
		/* FIXME: how to specify bus ??? */
		val |= (1 << MPI_L2PCFG_CFG_TYPE_SHIFT);
	}
	bcm_mpi_writel(val, MPI_L2PCFG_REG);

	return 0;
}