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
struct scsi_host_template {int dummy; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct esp {int scsi_id; int scsi_id_mask; int cfreq; void* regs; void* dma_regs; int /*<<< orphan*/  command_block_dma; int /*<<< orphan*/  command_block; int /*<<< orphan*/ * dev; struct Scsi_Host* host; int /*<<< orphan*/ * ops; } ;
struct Scsi_Host {int max_id; int this_id; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct esp*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct esp*) ; 
 void* ioremap_nocache (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct esp*) ; 
 int /*<<< orphan*/  scsi_esp_intr ; 
 int scsi_esp_register (struct esp*) ; 
 struct scsi_host_template scsi_esp_template ; 
 struct Scsi_Host* scsi_host_alloc (struct scsi_host_template*,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 struct esp* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  sun3x_esp_ops ; 

__attribute__((used)) static int esp_sun3x_probe(struct platform_device *dev)
{
	struct scsi_host_template *tpnt = &scsi_esp_template;
	struct Scsi_Host *host;
	struct esp *esp;
	struct resource *res;
	int err = -ENOMEM;

	host = scsi_host_alloc(tpnt, sizeof(struct esp));
	if (!host)
		goto fail;

	host->max_id = 8;
	esp = shost_priv(host);

	esp->host = host;
	esp->dev = &dev->dev;
	esp->ops = &sun3x_esp_ops;

	res = platform_get_resource(dev, IORESOURCE_MEM, 0);
	if (!res || !res->start)
		goto fail_unlink;

	esp->regs = ioremap_nocache(res->start, 0x20);
	if (!esp->regs)
		goto fail_unmap_regs;

	res = platform_get_resource(dev, IORESOURCE_MEM, 1);
	if (!res || !res->start)
		goto fail_unmap_regs;

	esp->dma_regs = ioremap_nocache(res->start, 0x10);

	esp->command_block = dma_alloc_coherent(esp->dev, 16,
						&esp->command_block_dma,
						GFP_KERNEL);
	if (!esp->command_block)
		goto fail_unmap_regs_dma;

	host->irq = platform_get_irq(dev, 0);
	err = request_irq(host->irq, scsi_esp_intr, IRQF_SHARED,
			  "SUN3X ESP", esp);
	if (err < 0)
		goto fail_unmap_command_block;

	esp->scsi_id = 7;
	esp->host->this_id = esp->scsi_id;
	esp->scsi_id_mask = (1 << esp->scsi_id);
	esp->cfreq = 20000000;

	dev_set_drvdata(&dev->dev, esp);

	err = scsi_esp_register(esp);
	if (err)
		goto fail_free_irq;

	return 0;

fail_free_irq:
	free_irq(host->irq, esp);
fail_unmap_command_block:
	dma_free_coherent(esp->dev, 16,
			  esp->command_block,
			  esp->command_block_dma);
fail_unmap_regs_dma:
	iounmap(esp->dma_regs);
fail_unmap_regs:
	iounmap(esp->regs);
fail_unlink:
	scsi_host_put(host);
fail:
	return err;
}