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
struct zorro_esp_priv {int /*<<< orphan*/  board_base; scalar_t__ zorro3; struct esp* esp; } ;
struct zorro_dev {int /*<<< orphan*/  dev; } ;
struct esp {int /*<<< orphan*/  regs; int /*<<< orphan*/  dma_regs; int /*<<< orphan*/  command_block_dma; int /*<<< orphan*/  command_block; int /*<<< orphan*/  dev; struct Scsi_Host* host; } ;
struct Scsi_Host {int base; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 struct zorro_esp_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct esp*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct zorro_esp_priv*) ; 
 int /*<<< orphan*/  scsi_esp_unregister (struct esp*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  zorro_release_device (struct zorro_dev*) ; 

__attribute__((used)) static void zorro_esp_remove(struct zorro_dev *z)
{
	struct zorro_esp_priv *zep = dev_get_drvdata(&z->dev);
	struct esp *esp	= zep->esp;
	struct Scsi_Host *host = esp->host;

	scsi_esp_unregister(esp);

	free_irq(host->irq, esp);
	dma_free_coherent(esp->dev, 16,
			  esp->command_block,
			  esp->command_block_dma);

	if (zep->zorro3) {
		iounmap(zep->board_base);
		iounmap(esp->dma_regs);
	}

	if (host->base > 0xffffff)
		iounmap(esp->regs);

	scsi_host_put(host);

	zorro_release_device(z);

	kfree(zep);
}