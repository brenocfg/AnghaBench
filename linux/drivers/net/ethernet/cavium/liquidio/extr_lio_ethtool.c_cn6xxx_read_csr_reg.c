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
typedef  int u32 ;
struct octeon_device {int num_oqs; int /*<<< orphan*/  pcie_port; } ;

/* Variables and functions */
 int CN6XXX_BAR1_REG (int,int /*<<< orphan*/ ) ; 
 int CN6XXX_DMA_CNT (int) ; 
 int CN6XXX_DMA_PKT_INT_LEVEL (int) ; 
 int CN6XXX_DMA_TIME_INT_LEVEL (int) ; 
 int CN6XXX_SLI_INT_ENB64_PORT0 ; 
 int CN6XXX_SLI_INT_ENB64_PORT1 ; 
 int CN6XXX_SLI_INT_SUM64 ; 
 int CN6XXX_SLI_IQ_DOORBELL (int) ; 
 int CN6XXX_SLI_IQ_INSTR_COUNT (int) ; 
 int CN6XXX_SLI_OQ_INT_LEVEL_PKTS ; 
 int CN6XXX_SLI_OQ_INT_LEVEL_TIME ; 
 int CN6XXX_SLI_OQ_PKTS_CREDIT (int) ; 
 int CN6XXX_SLI_OQ_PKTS_SENT (int) ; 
 int CN6XXX_WIN_RD_ADDR_HI ; 
 int CN6XXX_WIN_RD_ADDR_LO ; 
 int CN6XXX_WIN_WR_ADDR_HI ; 
 int CN6XXX_WIN_WR_ADDR_LO ; 
 int CN6XXX_WIN_WR_DATA_HI ; 
 int CN6XXX_WIN_WR_DATA_LO ; 
 int CN6XXX_WIN_WR_MASK_REG ; 
 int lio_pci_readq (struct octeon_device*,int) ; 
 int octeon_read_csr (struct octeon_device*,int) ; 
 scalar_t__ sprintf (char*,char*,...) ; 

__attribute__((used)) static int cn6xxx_read_csr_reg(char *s, struct octeon_device *oct)
{
	u32 reg;
	int i, len = 0;

	/* PCI  Window Registers */

	len += sprintf(s + len, "\n\t Octeon CSR Registers\n\n");
	reg = CN6XXX_WIN_WR_ADDR_LO;
	len += sprintf(s + len, "\n[%02x] (WIN_WR_ADDR_LO): %08x\n",
		       CN6XXX_WIN_WR_ADDR_LO, octeon_read_csr(oct, reg));
	reg = CN6XXX_WIN_WR_ADDR_HI;
	len += sprintf(s + len, "[%02x] (WIN_WR_ADDR_HI): %08x\n",
		       CN6XXX_WIN_WR_ADDR_HI, octeon_read_csr(oct, reg));
	reg = CN6XXX_WIN_RD_ADDR_LO;
	len += sprintf(s + len, "[%02x] (WIN_RD_ADDR_LO): %08x\n",
		       CN6XXX_WIN_RD_ADDR_LO, octeon_read_csr(oct, reg));
	reg = CN6XXX_WIN_RD_ADDR_HI;
	len += sprintf(s + len, "[%02x] (WIN_RD_ADDR_HI): %08x\n",
		       CN6XXX_WIN_RD_ADDR_HI, octeon_read_csr(oct, reg));
	reg = CN6XXX_WIN_WR_DATA_LO;
	len += sprintf(s + len, "[%02x] (WIN_WR_DATA_LO): %08x\n",
		       CN6XXX_WIN_WR_DATA_LO, octeon_read_csr(oct, reg));
	reg = CN6XXX_WIN_WR_DATA_HI;
	len += sprintf(s + len, "[%02x] (WIN_WR_DATA_HI): %08x\n",
		       CN6XXX_WIN_WR_DATA_HI, octeon_read_csr(oct, reg));
	len += sprintf(s + len, "[%02x] (WIN_WR_MASK_REG): %08x\n",
		       CN6XXX_WIN_WR_MASK_REG,
		       octeon_read_csr(oct, CN6XXX_WIN_WR_MASK_REG));

	/* PCI  Interrupt Register */
	len += sprintf(s + len, "\n[%x] (INT_ENABLE PORT 0): %08x\n",
		       CN6XXX_SLI_INT_ENB64_PORT0, octeon_read_csr(oct,
						CN6XXX_SLI_INT_ENB64_PORT0));
	len += sprintf(s + len, "\n[%x] (INT_ENABLE PORT 1): %08x\n",
		       CN6XXX_SLI_INT_ENB64_PORT1,
		       octeon_read_csr(oct, CN6XXX_SLI_INT_ENB64_PORT1));
	len += sprintf(s + len, "[%x] (INT_SUM): %08x\n", CN6XXX_SLI_INT_SUM64,
		       octeon_read_csr(oct, CN6XXX_SLI_INT_SUM64));

	/* PCI  Output queue registers */
	for (i = 0; i < oct->num_oqs; i++) {
		reg = CN6XXX_SLI_OQ_PKTS_SENT(i);
		len += sprintf(s + len, "\n[%x] (PKTS_SENT_%d): %08x\n",
			       reg, i, octeon_read_csr(oct, reg));
		reg = CN6XXX_SLI_OQ_PKTS_CREDIT(i);
		len += sprintf(s + len, "[%x] (PKT_CREDITS_%d): %08x\n",
			       reg, i, octeon_read_csr(oct, reg));
	}
	reg = CN6XXX_SLI_OQ_INT_LEVEL_PKTS;
	len += sprintf(s + len, "\n[%x] (PKTS_SENT_INT_LEVEL): %08x\n",
		       reg, octeon_read_csr(oct, reg));
	reg = CN6XXX_SLI_OQ_INT_LEVEL_TIME;
	len += sprintf(s + len, "[%x] (PKTS_SENT_TIME): %08x\n",
		       reg, octeon_read_csr(oct, reg));

	/* PCI  Input queue registers */
	for (i = 0; i <= 3; i++) {
		u32 reg;

		reg = CN6XXX_SLI_IQ_DOORBELL(i);
		len += sprintf(s + len, "\n[%x] (INSTR_DOORBELL_%d): %08x\n",
			       reg, i, octeon_read_csr(oct, reg));
		reg = CN6XXX_SLI_IQ_INSTR_COUNT(i);
		len += sprintf(s + len, "[%x] (INSTR_COUNT_%d): %08x\n",
			       reg, i, octeon_read_csr(oct, reg));
	}

	/* PCI  DMA registers */

	len += sprintf(s + len, "\n[%x] (DMA_CNT_0): %08x\n",
		       CN6XXX_DMA_CNT(0),
		       octeon_read_csr(oct, CN6XXX_DMA_CNT(0)));
	reg = CN6XXX_DMA_PKT_INT_LEVEL(0);
	len += sprintf(s + len, "[%x] (DMA_INT_LEV_0): %08x\n",
		       CN6XXX_DMA_PKT_INT_LEVEL(0), octeon_read_csr(oct, reg));
	reg = CN6XXX_DMA_TIME_INT_LEVEL(0);
	len += sprintf(s + len, "[%x] (DMA_TIME_0): %08x\n",
		       CN6XXX_DMA_TIME_INT_LEVEL(0),
		       octeon_read_csr(oct, reg));

	len += sprintf(s + len, "\n[%x] (DMA_CNT_1): %08x\n",
		       CN6XXX_DMA_CNT(1),
		       octeon_read_csr(oct, CN6XXX_DMA_CNT(1)));
	reg = CN6XXX_DMA_PKT_INT_LEVEL(1);
	len += sprintf(s + len, "[%x] (DMA_INT_LEV_1): %08x\n",
		       CN6XXX_DMA_PKT_INT_LEVEL(1),
		       octeon_read_csr(oct, reg));
	reg = CN6XXX_DMA_PKT_INT_LEVEL(1);
	len += sprintf(s + len, "[%x] (DMA_TIME_1): %08x\n",
		       CN6XXX_DMA_TIME_INT_LEVEL(1),
		       octeon_read_csr(oct, reg));

	/* PCI  Index registers */

	len += sprintf(s + len, "\n");

	for (i = 0; i < 16; i++) {
		reg = lio_pci_readq(oct, CN6XXX_BAR1_REG(i, oct->pcie_port));
		len += sprintf(s + len, "[%llx] (BAR1_INDEX_%02d): %08x\n",
			       CN6XXX_BAR1_REG(i, oct->pcie_port), i, reg);
	}

	return len;
}