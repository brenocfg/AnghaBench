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
typedef  int u8 ;
typedef  int u32 ;
struct esp {scalar_t__ rev; int prev_hme_dmacsr; scalar_t__ dmarev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_ADDR ; 
 int /*<<< orphan*/  DMA_COUNT ; 
 int /*<<< orphan*/  DMA_CSR ; 
 int DMA_ENABLE ; 
 int DMA_SCSI_DISAB ; 
 int DMA_ST_WRITE ; 
 int ESP_CMD_DMA ; 
 int /*<<< orphan*/  ESP_TCLOW ; 
 int /*<<< orphan*/  ESP_TCMED ; 
 scalar_t__ FASHME ; 
 int /*<<< orphan*/  FAS_RHI ; 
 int /*<<< orphan*/  FAS_RLO ; 
 int PAGE_ALIGN (int) ; 
 int dma_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_write32 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ dvmaesc1 ; 
 int /*<<< orphan*/  sbus_esp_write8 (struct esp*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_esp_cmd (struct esp*,int) ; 

__attribute__((used)) static void sbus_esp_send_dma_cmd(struct esp *esp, u32 addr, u32 esp_count,
				  u32 dma_count, int write, u8 cmd)
{
	u32 csr;

	BUG_ON(!(cmd & ESP_CMD_DMA));

	sbus_esp_write8(esp, (esp_count >> 0) & 0xff, ESP_TCLOW);
	sbus_esp_write8(esp, (esp_count >> 8) & 0xff, ESP_TCMED);
	if (esp->rev == FASHME) {
		sbus_esp_write8(esp, (esp_count >> 16) & 0xff, FAS_RLO);
		sbus_esp_write8(esp, 0, FAS_RHI);

		scsi_esp_cmd(esp, cmd);

		csr = esp->prev_hme_dmacsr;
		csr |= DMA_SCSI_DISAB | DMA_ENABLE;
		if (write)
			csr |= DMA_ST_WRITE;
		else
			csr &= ~DMA_ST_WRITE;
		esp->prev_hme_dmacsr = csr;

		dma_write32(dma_count, DMA_COUNT);
		dma_write32(addr, DMA_ADDR);
		dma_write32(csr, DMA_CSR);
	} else {
		csr = dma_read32(DMA_CSR);
		csr |= DMA_ENABLE;
		if (write)
			csr |= DMA_ST_WRITE;
		else
			csr &= ~DMA_ST_WRITE;
		dma_write32(csr, DMA_CSR);
		if (esp->dmarev == dvmaesc1) {
			u32 end = PAGE_ALIGN(addr + dma_count + 16U);
			dma_write32(end - addr, DMA_COUNT);
		}
		dma_write32(addr, DMA_ADDR);

		scsi_esp_cmd(esp, cmd);
	}

}