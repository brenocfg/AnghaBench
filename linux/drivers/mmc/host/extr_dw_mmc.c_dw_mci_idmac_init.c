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
struct idmac_desc_64addr {int des6; int des7; int des0; void* des3; scalar_t__ des1; scalar_t__ des2; } ;
struct idmac_desc {int des6; int des7; int des0; void* des3; scalar_t__ des1; scalar_t__ des2; } ;
struct dw_mci {int dma_64bit_address; int ring_size; int sg_dma; struct idmac_desc_64addr* sg_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBADDR ; 
 int /*<<< orphan*/  DBADDRL ; 
 int /*<<< orphan*/  DBADDRU ; 
 int DESC_RING_BUF_SZ ; 
 int /*<<< orphan*/  IDINTEN ; 
 int /*<<< orphan*/  IDINTEN64 ; 
 int IDMAC_DES0_ER ; 
 int IDMAC_INT_CLR ; 
 int /*<<< orphan*/  IDSTS ; 
 int /*<<< orphan*/  IDSTS64 ; 
 int SDMMC_IDMAC_INT_NI ; 
 int SDMMC_IDMAC_INT_RI ; 
 int SDMMC_IDMAC_INT_TI ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dw_mci_idmac_reset (struct dw_mci*) ; 
 int /*<<< orphan*/  mci_writel (struct dw_mci*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dw_mci_idmac_init(struct dw_mci *host)
{
	int i;

	if (host->dma_64bit_address == 1) {
		struct idmac_desc_64addr *p;
		/* Number of descriptors in the ring buffer */
		host->ring_size =
			DESC_RING_BUF_SZ / sizeof(struct idmac_desc_64addr);

		/* Forward link the descriptor list */
		for (i = 0, p = host->sg_cpu; i < host->ring_size - 1;
								i++, p++) {
			p->des6 = (host->sg_dma +
					(sizeof(struct idmac_desc_64addr) *
							(i + 1))) & 0xffffffff;

			p->des7 = (u64)(host->sg_dma +
					(sizeof(struct idmac_desc_64addr) *
							(i + 1))) >> 32;
			/* Initialize reserved and buffer size fields to "0" */
			p->des0 = 0;
			p->des1 = 0;
			p->des2 = 0;
			p->des3 = 0;
		}

		/* Set the last descriptor as the end-of-ring descriptor */
		p->des6 = host->sg_dma & 0xffffffff;
		p->des7 = (u64)host->sg_dma >> 32;
		p->des0 = IDMAC_DES0_ER;

	} else {
		struct idmac_desc *p;
		/* Number of descriptors in the ring buffer */
		host->ring_size =
			DESC_RING_BUF_SZ / sizeof(struct idmac_desc);

		/* Forward link the descriptor list */
		for (i = 0, p = host->sg_cpu;
		     i < host->ring_size - 1;
		     i++, p++) {
			p->des3 = cpu_to_le32(host->sg_dma +
					(sizeof(struct idmac_desc) * (i + 1)));
			p->des0 = 0;
			p->des1 = 0;
		}

		/* Set the last descriptor as the end-of-ring descriptor */
		p->des3 = cpu_to_le32(host->sg_dma);
		p->des0 = cpu_to_le32(IDMAC_DES0_ER);
	}

	dw_mci_idmac_reset(host);

	if (host->dma_64bit_address == 1) {
		/* Mask out interrupts - get Tx & Rx complete only */
		mci_writel(host, IDSTS64, IDMAC_INT_CLR);
		mci_writel(host, IDINTEN64, SDMMC_IDMAC_INT_NI |
				SDMMC_IDMAC_INT_RI | SDMMC_IDMAC_INT_TI);

		/* Set the descriptor base address */
		mci_writel(host, DBADDRL, host->sg_dma & 0xffffffff);
		mci_writel(host, DBADDRU, (u64)host->sg_dma >> 32);

	} else {
		/* Mask out interrupts - get Tx & Rx complete only */
		mci_writel(host, IDSTS, IDMAC_INT_CLR);
		mci_writel(host, IDINTEN, SDMMC_IDMAC_INT_NI |
				SDMMC_IDMAC_INT_RI | SDMMC_IDMAC_INT_TI);

		/* Set the descriptor base address */
		mci_writel(host, DBADDR, host->sg_dma);
	}

	return 0;
}