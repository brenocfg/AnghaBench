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
struct esp_cmd_entry {int /*<<< orphan*/  flags; } ;
struct esp {int sreg; struct esp_cmd_entry* active_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_CMD_FLAG_RESIDUAL ; 
 int ESP_DIP ; 
 int /*<<< orphan*/  ESP_DMA_CMD ; 
 int ESP_DMA_CMD_BLAST ; 
 int ESP_DMA_CMD_DIR ; 
 int ESP_DMA_CMD_IDLE ; 
 int /*<<< orphan*/  ESP_DMA_STATUS ; 
 int ESP_DMA_STAT_BCMPLT ; 
 int ESP_DOP ; 
 int /*<<< orphan*/  ESP_FFLAGS ; 
 int ESP_FF_FBYTES ; 
 int ESP_STAT_PMASK ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  esp_dma_log (char*,int,int) ; 
 int pci_esp_read8 (struct esp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_esp_write8 (struct esp*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pci_esp_dma_drain(struct esp *esp)
{
	u8 resid;
	int lim = 1000;


	if ((esp->sreg & ESP_STAT_PMASK) == ESP_DOP ||
	    (esp->sreg & ESP_STAT_PMASK) == ESP_DIP)
		/* Data-In or Data-Out, nothing to be done */
		return;

	while (--lim > 0) {
		resid = pci_esp_read8(esp, ESP_FFLAGS) & ESP_FF_FBYTES;
		if (resid <= 1)
			break;
		cpu_relax();
	}

	/*
	 * When there is a residual BCMPLT will never be set
	 * (obviously). But we still have to issue the BLAST
	 * command, otherwise the data will not being transferred.
	 * But we'll never know when the BLAST operation is
	 * finished. So check for some time and give up eventually.
	 */
	lim = 1000;
	pci_esp_write8(esp, ESP_DMA_CMD_DIR | ESP_DMA_CMD_BLAST, ESP_DMA_CMD);
	while (pci_esp_read8(esp, ESP_DMA_STATUS) & ESP_DMA_STAT_BCMPLT) {
		if (--lim == 0)
			break;
		cpu_relax();
	}
	pci_esp_write8(esp, ESP_DMA_CMD_DIR | ESP_DMA_CMD_IDLE, ESP_DMA_CMD);
	esp_dma_log("DMA blast done (%d tries, %d bytes left)\n", lim, resid);
	/* BLAST residual handling is currently untested */
	if (WARN_ON_ONCE(resid == 1)) {
		struct esp_cmd_entry *ent = esp->active_cmd;

		ent->flags |= ESP_CMD_FLAG_RESIDUAL;
	}
}