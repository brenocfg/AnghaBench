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
typedef  int /*<<< orphan*/  u64 ;
typedef  long u32 ;
struct octeon_device {TYPE_1__* pci_dev; int /*<<< orphan*/  pf_num; int /*<<< orphan*/  pcie_port; scalar_t__ chip; } ;
struct octeon_cn23xx_pf {scalar_t__ intr_sum_reg64; scalar_t__ intr_enb_reg64; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 long CN23XX_CONFIG_PCIE_DEVCTL ; 
 int /*<<< orphan*/  CN23XX_DPI_CTL ; 
 int /*<<< orphan*/  CN23XX_DPI_DMA_CONTROL ; 
 int /*<<< orphan*/  CN23XX_DPI_DMA_ENG_BUF (int) ; 
 int /*<<< orphan*/  CN23XX_DPI_DMA_ENG_ENB (int) ; 
 int /*<<< orphan*/  CN23XX_DPI_SLI_PRTX_CFG (int /*<<< orphan*/ ) ; 
 int CN23XX_MAX_INPUT_QUEUES ; 
 int CN23XX_MAX_MACS ; 
 int CN23XX_MAX_OUTPUT_QUEUES ; 
 int /*<<< orphan*/  CN23XX_RST_SOFT_RST ; 
 long CN23XX_SLI_IQ_BASE_ADDR64 (int) ; 
 long CN23XX_SLI_IQ_DOORBELL (int) ; 
 long CN23XX_SLI_IQ_INSTR_COUNT64 (int) ; 
 long CN23XX_SLI_IQ_PKT_CONTROL64 (int) ; 
 long CN23XX_SLI_IQ_SIZE (int) ; 
 long CN23XX_SLI_OQ_BASE_ADDR64 (int) ; 
 long CN23XX_SLI_OQ_BUFF_INFO_SIZE (int) ; 
 long CN23XX_SLI_OQ_PKTS_CREDIT (int) ; 
 long CN23XX_SLI_OQ_PKTS_SENT (int) ; 
 long CN23XX_SLI_OQ_PKT_CONTROL (int) ; 
 long CN23XX_SLI_OQ_PKT_INT_LEVELS (int) ; 
 long CN23XX_SLI_OQ_SIZE (int) ; 
 long CN23XX_SLI_OQ_WMARK ; 
 long CN23XX_SLI_PKT_CNT_INT ; 
 long CN23XX_SLI_PKT_IOQ_RING_RST ; 
 long CN23XX_SLI_PKT_MAC_RINFO64 (int,int /*<<< orphan*/ ) ; 
 long CN23XX_SLI_PKT_TIME_INT ; 
 long CN23XX_SLI_S2M_PORTX_CTL (int /*<<< orphan*/ ) ; 
 long CN23XX_SLI_SCRATCH1 ; 
 long CN23XX_WIN_WR_MASK_REG ; 
 int /*<<< orphan*/  CVM_CAST64 (long) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  lio_pci_readq (struct octeon_device*,int /*<<< orphan*/ ) ; 
 long octeon_read_csr (struct octeon_device*,long) ; 
 long octeon_read_csr64 (struct octeon_device*,long) ; 
 int /*<<< orphan*/  pci_read_config_dword (TYPE_1__*,long,long*) ; 
 long readq (scalar_t__) ; 

void cn23xx_dump_pf_initialized_regs(struct octeon_device *oct)
{
	int i = 0;
	u32 regval = 0;
	struct octeon_cn23xx_pf *cn23xx = (struct octeon_cn23xx_pf *)oct->chip;

	/*In cn23xx_soft_reset*/
	dev_dbg(&oct->pci_dev->dev, "%s[%llx] : 0x%llx\n",
		"CN23XX_WIN_WR_MASK_REG", CVM_CAST64(CN23XX_WIN_WR_MASK_REG),
		CVM_CAST64(octeon_read_csr64(oct, CN23XX_WIN_WR_MASK_REG)));
	dev_dbg(&oct->pci_dev->dev, "%s[%llx] : 0x%016llx\n",
		"CN23XX_SLI_SCRATCH1", CVM_CAST64(CN23XX_SLI_SCRATCH1),
		CVM_CAST64(octeon_read_csr64(oct, CN23XX_SLI_SCRATCH1)));
	dev_dbg(&oct->pci_dev->dev, "%s[%llx] : 0x%016llx\n",
		"CN23XX_RST_SOFT_RST", CN23XX_RST_SOFT_RST,
		lio_pci_readq(oct, CN23XX_RST_SOFT_RST));

	/*In cn23xx_set_dpi_regs*/
	dev_dbg(&oct->pci_dev->dev, "%s[%llx] : 0x%016llx\n",
		"CN23XX_DPI_DMA_CONTROL", CN23XX_DPI_DMA_CONTROL,
		lio_pci_readq(oct, CN23XX_DPI_DMA_CONTROL));

	for (i = 0; i < 6; i++) {
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_DPI_DMA_ENG_ENB", i,
			CN23XX_DPI_DMA_ENG_ENB(i),
			lio_pci_readq(oct, CN23XX_DPI_DMA_ENG_ENB(i)));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_DPI_DMA_ENG_BUF", i,
			CN23XX_DPI_DMA_ENG_BUF(i),
			lio_pci_readq(oct, CN23XX_DPI_DMA_ENG_BUF(i)));
	}

	dev_dbg(&oct->pci_dev->dev, "%s[%llx] : 0x%016llx\n", "CN23XX_DPI_CTL",
		CN23XX_DPI_CTL, lio_pci_readq(oct, CN23XX_DPI_CTL));

	/*In cn23xx_setup_pcie_mps and cn23xx_setup_pcie_mrrs */
	pci_read_config_dword(oct->pci_dev, CN23XX_CONFIG_PCIE_DEVCTL, &regval);
	dev_dbg(&oct->pci_dev->dev, "%s[%llx] : 0x%016llx\n",
		"CN23XX_CONFIG_PCIE_DEVCTL",
		CVM_CAST64(CN23XX_CONFIG_PCIE_DEVCTL), CVM_CAST64(regval));

	dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
		"CN23XX_DPI_SLI_PRTX_CFG", oct->pcie_port,
		CN23XX_DPI_SLI_PRTX_CFG(oct->pcie_port),
		lio_pci_readq(oct, CN23XX_DPI_SLI_PRTX_CFG(oct->pcie_port)));

	/*In cn23xx_specific_regs_setup */
	dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
		"CN23XX_SLI_S2M_PORTX_CTL", oct->pcie_port,
		CVM_CAST64(CN23XX_SLI_S2M_PORTX_CTL(oct->pcie_port)),
		CVM_CAST64(octeon_read_csr64(
			oct, CN23XX_SLI_S2M_PORTX_CTL(oct->pcie_port))));

	dev_dbg(&oct->pci_dev->dev, "%s[%llx] : 0x%016llx\n",
		"CN23XX_SLI_RING_RST", CVM_CAST64(CN23XX_SLI_PKT_IOQ_RING_RST),
		(u64)octeon_read_csr64(oct, CN23XX_SLI_PKT_IOQ_RING_RST));

	/*In cn23xx_setup_global_mac_regs*/
	for (i = 0; i < CN23XX_MAX_MACS; i++) {
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_PKT_MAC_RINFO64", i,
			CVM_CAST64(CN23XX_SLI_PKT_MAC_RINFO64(i, oct->pf_num)),
			CVM_CAST64(octeon_read_csr64
				(oct, CN23XX_SLI_PKT_MAC_RINFO64
					(i, oct->pf_num))));
	}

	/*In cn23xx_setup_global_input_regs*/
	for (i = 0; i < CN23XX_MAX_INPUT_QUEUES; i++) {
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_IQ_PKT_CONTROL64", i,
			CVM_CAST64(CN23XX_SLI_IQ_PKT_CONTROL64(i)),
			CVM_CAST64(octeon_read_csr64
				(oct, CN23XX_SLI_IQ_PKT_CONTROL64(i))));
	}

	/*In cn23xx_setup_global_output_regs*/
	dev_dbg(&oct->pci_dev->dev, "%s[%llx] : 0x%016llx\n",
		"CN23XX_SLI_OQ_WMARK", CVM_CAST64(CN23XX_SLI_OQ_WMARK),
		CVM_CAST64(octeon_read_csr64(oct, CN23XX_SLI_OQ_WMARK)));

	for (i = 0; i < CN23XX_MAX_OUTPUT_QUEUES; i++) {
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_OQ_PKT_CONTROL", i,
			CVM_CAST64(CN23XX_SLI_OQ_PKT_CONTROL(i)),
			CVM_CAST64(octeon_read_csr(
				oct, CN23XX_SLI_OQ_PKT_CONTROL(i))));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_OQ_PKT_INT_LEVELS", i,
			CVM_CAST64(CN23XX_SLI_OQ_PKT_INT_LEVELS(i)),
			CVM_CAST64(octeon_read_csr64(
				oct, CN23XX_SLI_OQ_PKT_INT_LEVELS(i))));
	}

	/*In cn23xx_enable_interrupt and cn23xx_disable_interrupt*/
	dev_dbg(&oct->pci_dev->dev, "%s[%llx] : 0x%016llx\n",
		"cn23xx->intr_enb_reg64",
		CVM_CAST64((long)(cn23xx->intr_enb_reg64)),
		CVM_CAST64(readq(cn23xx->intr_enb_reg64)));

	dev_dbg(&oct->pci_dev->dev, "%s[%llx] : 0x%016llx\n",
		"cn23xx->intr_sum_reg64",
		CVM_CAST64((long)(cn23xx->intr_sum_reg64)),
		CVM_CAST64(readq(cn23xx->intr_sum_reg64)));

	/*In cn23xx_setup_iq_regs*/
	for (i = 0; i < CN23XX_MAX_INPUT_QUEUES; i++) {
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_IQ_BASE_ADDR64", i,
			CVM_CAST64(CN23XX_SLI_IQ_BASE_ADDR64(i)),
			CVM_CAST64(octeon_read_csr64(
				oct, CN23XX_SLI_IQ_BASE_ADDR64(i))));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_IQ_SIZE", i,
			CVM_CAST64(CN23XX_SLI_IQ_SIZE(i)),
			CVM_CAST64(octeon_read_csr
				(oct, CN23XX_SLI_IQ_SIZE(i))));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_IQ_DOORBELL", i,
			CVM_CAST64(CN23XX_SLI_IQ_DOORBELL(i)),
			CVM_CAST64(octeon_read_csr64(
				oct, CN23XX_SLI_IQ_DOORBELL(i))));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_IQ_INSTR_COUNT64", i,
			CVM_CAST64(CN23XX_SLI_IQ_INSTR_COUNT64(i)),
			CVM_CAST64(octeon_read_csr64(
				oct, CN23XX_SLI_IQ_INSTR_COUNT64(i))));
	}

	/*In cn23xx_setup_oq_regs*/
	for (i = 0; i < CN23XX_MAX_OUTPUT_QUEUES; i++) {
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_OQ_BASE_ADDR64", i,
			CVM_CAST64(CN23XX_SLI_OQ_BASE_ADDR64(i)),
			CVM_CAST64(octeon_read_csr64(
				oct, CN23XX_SLI_OQ_BASE_ADDR64(i))));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_OQ_SIZE", i,
			CVM_CAST64(CN23XX_SLI_OQ_SIZE(i)),
			CVM_CAST64(octeon_read_csr
				(oct, CN23XX_SLI_OQ_SIZE(i))));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_OQ_BUFF_INFO_SIZE", i,
			CVM_CAST64(CN23XX_SLI_OQ_BUFF_INFO_SIZE(i)),
			CVM_CAST64(octeon_read_csr(
				oct, CN23XX_SLI_OQ_BUFF_INFO_SIZE(i))));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_OQ_PKTS_SENT", i,
			CVM_CAST64(CN23XX_SLI_OQ_PKTS_SENT(i)),
			CVM_CAST64(octeon_read_csr64(
				oct, CN23XX_SLI_OQ_PKTS_SENT(i))));
		dev_dbg(&oct->pci_dev->dev, "%s(%d)[%llx] : 0x%016llx\n",
			"CN23XX_SLI_OQ_PKTS_CREDIT", i,
			CVM_CAST64(CN23XX_SLI_OQ_PKTS_CREDIT(i)),
			CVM_CAST64(octeon_read_csr64(
				oct, CN23XX_SLI_OQ_PKTS_CREDIT(i))));
	}

	dev_dbg(&oct->pci_dev->dev, "%s[%llx] : 0x%016llx\n",
		"CN23XX_SLI_PKT_TIME_INT",
		CVM_CAST64(CN23XX_SLI_PKT_TIME_INT),
		CVM_CAST64(octeon_read_csr64(oct, CN23XX_SLI_PKT_TIME_INT)));
	dev_dbg(&oct->pci_dev->dev, "%s[%llx] : 0x%016llx\n",
		"CN23XX_SLI_PKT_CNT_INT",
		CVM_CAST64(CN23XX_SLI_PKT_CNT_INT),
		CVM_CAST64(octeon_read_csr64(oct, CN23XX_SLI_PKT_CNT_INT)));
}