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
struct esp_cmd_entry {int /*<<< orphan*/ * sense_ptr; int /*<<< orphan*/  sense_dma; } ;
struct esp {int flags; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ESP_FLAG_NO_DMA_MAP ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esp_unmap_sense(struct esp *esp, struct esp_cmd_entry *ent)
{
	if (!(esp->flags & ESP_FLAG_NO_DMA_MAP))
		dma_unmap_single(esp->dev, ent->sense_dma,
				 SCSI_SENSE_BUFFERSIZE, DMA_FROM_DEVICE);
	ent->sense_ptr = NULL;
}