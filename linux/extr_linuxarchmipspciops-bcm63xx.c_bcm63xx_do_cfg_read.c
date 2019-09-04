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

/* Variables and functions */
 int /*<<< orphan*/  MPI_L2PCFG_REG ; 
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  __raw_readl (int /*<<< orphan*/ ) ; 
 scalar_t__ bcm63xx_setup_cfg_access (int,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  bcm_mpi_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iob () ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iospace_start ; 
 int /*<<< orphan*/  postprocess_read (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int bcm63xx_do_cfg_read(int type, unsigned int busn,
				unsigned int devfn, int where, int size,
				u32 *val)
{
	u32 data;

	/* two phase cycle, first we write address, then read data at
	 * another location, caller already has a spinlock so no need
	 * to add one here  */
	if (bcm63xx_setup_cfg_access(type, busn, devfn, where))
		return PCIBIOS_DEVICE_NOT_FOUND;
	iob();
	data = le32_to_cpu(__raw_readl(pci_iospace_start));
	/* restore IO space normal behaviour */
	bcm_mpi_writel(0, MPI_L2PCFG_REG);

	*val = postprocess_read(data, where, size);

	return PCIBIOS_SUCCESSFUL;
}