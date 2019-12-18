#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct esp {size_t rev; int cfreq; TYPE_1__* host; int /*<<< orphan*/  dev; int /*<<< orphan*/  scsi_id; int /*<<< orphan*/  cfact; int /*<<< orphan*/  dma_regs; int /*<<< orphan*/  regs; scalar_t__ num_tags; } ;
struct TYPE_3__ {int cmd_per_lun; int unique_id; int /*<<< orphan*/  irq; int /*<<< orphan*/  max_lun; int /*<<< orphan*/  transportt; } ;

/* Variables and functions */
 scalar_t__ ESP_DEFAULT_TAGS ; 
 int /*<<< orphan*/  ESP_MAX_LUN ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  esp_bootup_reset (struct esp*) ; 
 int /*<<< orphan*/  esp_bus_reset_settle ; 
 int /*<<< orphan*/ * esp_chip_names ; 
 int /*<<< orphan*/  esp_get_revision (struct esp*) ; 
 int /*<<< orphan*/  esp_init_swstate (struct esp*) ; 
 int /*<<< orphan*/  esp_set_clock_params (struct esp*) ; 
 int /*<<< orphan*/  esp_transport_template ; 
 int scsi_add_host (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_scan_host (TYPE_1__*) ; 
 int /*<<< orphan*/  ssleep (int /*<<< orphan*/ ) ; 

int scsi_esp_register(struct esp *esp)
{
	static int instance;
	int err;

	if (!esp->num_tags)
		esp->num_tags = ESP_DEFAULT_TAGS;
	esp->host->transportt = esp_transport_template;
	esp->host->max_lun = ESP_MAX_LUN;
	esp->host->cmd_per_lun = 2;
	esp->host->unique_id = instance;

	esp_set_clock_params(esp);

	esp_get_revision(esp);

	esp_init_swstate(esp);

	esp_bootup_reset(esp);

	dev_printk(KERN_INFO, esp->dev, "esp%u: regs[%1p:%1p] irq[%u]\n",
		   esp->host->unique_id, esp->regs, esp->dma_regs,
		   esp->host->irq);
	dev_printk(KERN_INFO, esp->dev,
		   "esp%u: is a %s, %u MHz (ccf=%u), SCSI ID %u\n",
		   esp->host->unique_id, esp_chip_names[esp->rev],
		   esp->cfreq / 1000000, esp->cfact, esp->scsi_id);

	/* Let the SCSI bus reset settle. */
	ssleep(esp_bus_reset_settle);

	err = scsi_add_host(esp->host, esp->dev);
	if (err)
		return err;

	instance++;

	scsi_scan_host(esp->host);

	return 0;
}