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
struct scsi_host_template {int dummy; } ;
struct platform_device {int /*<<< orphan*/ * resource; int /*<<< orphan*/  dev; } ;
struct esp {scalar_t__ dmarev; int /*<<< orphan*/  regs; int /*<<< orphan*/  command_block_dma; int /*<<< orphan*/  command_block; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * dev; struct Scsi_Host* host; } ;
struct Scsi_Host {int max_id; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CSR ; 
 int DMA_RST_SCSI ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ESP_FLAG_WIDE_CAPABLE ; 
 int /*<<< orphan*/  SBUS_ESP_REG_SIZE ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct esp*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_write32 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ dvmaesc1 ; 
 int /*<<< orphan*/  esp_sbus_get_props (struct esp*,struct platform_device*) ; 
 int esp_sbus_map_command_block (struct esp*) ; 
 int esp_sbus_map_regs (struct esp*,int) ; 
 int esp_sbus_register_irq (struct esp*) ; 
 int esp_sbus_setup_dma (struct esp*,struct platform_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct esp*) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbus_esp_ops ; 
 int scsi_esp_register (struct esp*) ; 
 struct scsi_host_template scsi_esp_template ; 
 struct Scsi_Host* scsi_host_alloc (struct scsi_host_template*,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 struct esp* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int esp_sbus_probe_one(struct platform_device *op,
			      struct platform_device *espdma, int hme)
{
	struct scsi_host_template *tpnt = &scsi_esp_template;
	struct Scsi_Host *host;
	struct esp *esp;
	int err;

	host = scsi_host_alloc(tpnt, sizeof(struct esp));

	err = -ENOMEM;
	if (!host)
		goto fail;

	host->max_id = (hme ? 16 : 8);
	esp = shost_priv(host);

	esp->host = host;
	esp->dev = &op->dev;
	esp->ops = &sbus_esp_ops;

	if (hme)
		esp->flags |= ESP_FLAG_WIDE_CAPABLE;

	err = esp_sbus_setup_dma(esp, espdma);
	if (err < 0)
		goto fail_unlink;

	err = esp_sbus_map_regs(esp, hme);
	if (err < 0)
		goto fail_unlink;

	err = esp_sbus_map_command_block(esp);
	if (err < 0)
		goto fail_unmap_regs;

	err = esp_sbus_register_irq(esp);
	if (err < 0)
		goto fail_unmap_command_block;

	esp_sbus_get_props(esp, espdma);

	/* Before we try to touch the ESP chip, ESC1 dma can
	 * come up with the reset bit set, so make sure that
	 * is clear first.
	 */
	if (esp->dmarev == dvmaesc1) {
		u32 val = dma_read32(DMA_CSR);

		dma_write32(val & ~DMA_RST_SCSI, DMA_CSR);
	}

	dev_set_drvdata(&op->dev, esp);

	err = scsi_esp_register(esp);
	if (err)
		goto fail_free_irq;

	return 0;

fail_free_irq:
	free_irq(host->irq, esp);
fail_unmap_command_block:
	dma_free_coherent(&op->dev, 16,
			  esp->command_block,
			  esp->command_block_dma);
fail_unmap_regs:
	of_iounmap(&op->resource[(hme ? 1 : 0)], esp->regs, SBUS_ESP_REG_SIZE);
fail_unlink:
	scsi_host_put(host);
fail:
	return err;
}