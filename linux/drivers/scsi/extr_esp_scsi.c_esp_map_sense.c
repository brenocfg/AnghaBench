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
struct esp_cmd_entry {uintptr_t sense_dma; scalar_t__ sense_ptr; TYPE_1__* cmd; } ;
struct esp {int flags; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ sense_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ESP_FLAG_NO_DMA_MAP ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 uintptr_t dma_map_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esp_map_sense(struct esp *esp, struct esp_cmd_entry *ent)
{
	ent->sense_ptr = ent->cmd->sense_buffer;
	if (esp->flags & ESP_FLAG_NO_DMA_MAP) {
		ent->sense_dma = (uintptr_t)ent->sense_ptr;
		return;
	}

	ent->sense_dma = dma_map_single(esp->dev, ent->sense_ptr,
					SCSI_SENSE_BUFFERSIZE, DMA_FROM_DEVICE);
}