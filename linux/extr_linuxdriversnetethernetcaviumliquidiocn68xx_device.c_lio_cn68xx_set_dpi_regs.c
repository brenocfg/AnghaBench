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
typedef  int u32 ;
struct octeon_device {TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN6XXX_DPI_CTL ; 
 int /*<<< orphan*/  CN6XXX_DPI_DMA_CONTROL ; 
 int CN6XXX_DPI_DMA_CTL_MASK ; 
 int /*<<< orphan*/  CN6XXX_DPI_DMA_ENG_BUF (int) ; 
 int /*<<< orphan*/  CN6XXX_DPI_DMA_ENG_ENB (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  lio_pci_readq (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_pci_writeq (struct octeon_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lio_cn68xx_set_dpi_regs(struct octeon_device *oct)
{
	u32 i;
	u32 fifo_sizes[6] = { 3, 3, 1, 1, 1, 8 };

	lio_pci_writeq(oct, CN6XXX_DPI_DMA_CTL_MASK, CN6XXX_DPI_DMA_CONTROL);
	dev_dbg(&oct->pci_dev->dev, "DPI_DMA_CONTROL: 0x%016llx\n",
		lio_pci_readq(oct, CN6XXX_DPI_DMA_CONTROL));

	for (i = 0; i < 6; i++) {
		/* Prevent service of instruction queue for all DMA engines
		 * Engine 5 will remain 0. Engines 0 - 4 will be setup by
		 * core.
		 */
		lio_pci_writeq(oct, 0, CN6XXX_DPI_DMA_ENG_ENB(i));
		lio_pci_writeq(oct, fifo_sizes[i], CN6XXX_DPI_DMA_ENG_BUF(i));
		dev_dbg(&oct->pci_dev->dev, "DPI_ENG_BUF%d: 0x%016llx\n", i,
			lio_pci_readq(oct, CN6XXX_DPI_DMA_ENG_BUF(i)));
	}

	/* DPI_SLI_PRT_CFG has MPS and MRRS settings that will be set
	 * separately.
	 */

	lio_pci_writeq(oct, 1, CN6XXX_DPI_CTL);
	dev_dbg(&oct->pci_dev->dev, "DPI_CTL: 0x%016llx\n",
		lio_pci_readq(oct, CN6XXX_DPI_CTL));
}