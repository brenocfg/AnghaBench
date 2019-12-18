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
typedef  int u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  test_desc ;
struct tg3_internal_buffer_desc {int addr_hi; int addr_lo; int nic_mbuf; int len; int cqid_sqid; int flags; } ;
struct tg3 {int /*<<< orphan*/  pdev; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFMGR_MODE ; 
 int ENODEV ; 
 int /*<<< orphan*/  FTQ_DMA_HIGH_READ_FIFO_ENQDEQ ; 
 int /*<<< orphan*/  FTQ_DMA_HIGH_WRITE_FIFO_ENQDEQ ; 
 int /*<<< orphan*/  FTQ_RCVBD_COMP_FIFO_ENQDEQ ; 
 int /*<<< orphan*/  FTQ_RCVDATA_COMP_FIFO_ENQDEQ ; 
 int /*<<< orphan*/  FTQ_RESET ; 
 int NIC_SRAM_DMA_DESC_POOL_BASE ; 
 int /*<<< orphan*/  RDMAC_MODE ; 
 int /*<<< orphan*/  RDMAC_MODE_ENABLE ; 
 int /*<<< orphan*/  RDMAC_STATUS ; 
 int /*<<< orphan*/  TG3PCI_MEM_WIN_BASE_ADDR ; 
 int /*<<< orphan*/  TG3PCI_MEM_WIN_DATA ; 
 int /*<<< orphan*/  WDMAC_MODE ; 
 int /*<<< orphan*/  WDMAC_MODE_ENABLE ; 
 int /*<<< orphan*/  WDMAC_STATUS ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int tr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tw32_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int tg3_do_test_dma(struct tg3 *tp, u32 *buf, dma_addr_t buf_dma,
			   int size, bool to_device)
{
	struct tg3_internal_buffer_desc test_desc;
	u32 sram_dma_descs;
	int i, ret;

	sram_dma_descs = NIC_SRAM_DMA_DESC_POOL_BASE;

	tw32(FTQ_RCVBD_COMP_FIFO_ENQDEQ, 0);
	tw32(FTQ_RCVDATA_COMP_FIFO_ENQDEQ, 0);
	tw32(RDMAC_STATUS, 0);
	tw32(WDMAC_STATUS, 0);

	tw32(BUFMGR_MODE, 0);
	tw32(FTQ_RESET, 0);

	test_desc.addr_hi = ((u64) buf_dma) >> 32;
	test_desc.addr_lo = buf_dma & 0xffffffff;
	test_desc.nic_mbuf = 0x00002100;
	test_desc.len = size;

	/*
	 * HP ZX1 was seeing test failures for 5701 cards running at 33Mhz
	 * the *second* time the tg3 driver was getting loaded after an
	 * initial scan.
	 *
	 * Broadcom tells me:
	 *   ...the DMA engine is connected to the GRC block and a DMA
	 *   reset may affect the GRC block in some unpredictable way...
	 *   The behavior of resets to individual blocks has not been tested.
	 *
	 * Broadcom noted the GRC reset will also reset all sub-components.
	 */
	if (to_device) {
		test_desc.cqid_sqid = (13 << 8) | 2;

		tw32_f(RDMAC_MODE, RDMAC_MODE_ENABLE);
		udelay(40);
	} else {
		test_desc.cqid_sqid = (16 << 8) | 7;

		tw32_f(WDMAC_MODE, WDMAC_MODE_ENABLE);
		udelay(40);
	}
	test_desc.flags = 0x00000005;

	for (i = 0; i < (sizeof(test_desc) / sizeof(u32)); i++) {
		u32 val;

		val = *(((u32 *)&test_desc) + i);
		pci_write_config_dword(tp->pdev, TG3PCI_MEM_WIN_BASE_ADDR,
				       sram_dma_descs + (i * sizeof(u32)));
		pci_write_config_dword(tp->pdev, TG3PCI_MEM_WIN_DATA, val);
	}
	pci_write_config_dword(tp->pdev, TG3PCI_MEM_WIN_BASE_ADDR, 0);

	if (to_device)
		tw32(FTQ_DMA_HIGH_READ_FIFO_ENQDEQ, sram_dma_descs);
	else
		tw32(FTQ_DMA_HIGH_WRITE_FIFO_ENQDEQ, sram_dma_descs);

	ret = -ENODEV;
	for (i = 0; i < 40; i++) {
		u32 val;

		if (to_device)
			val = tr32(FTQ_RCVBD_COMP_FIFO_ENQDEQ);
		else
			val = tr32(FTQ_RCVDATA_COMP_FIFO_ENQDEQ);
		if ((val & 0xffff) == sram_dma_descs) {
			ret = 0;
			break;
		}

		udelay(100);
	}

	return ret;
}