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
struct scsi_cmnd {int dummy; } ;
struct esp {int flags; } ;

/* Variables and functions */
 int ESP_FLAG_NO_DMA_MAP ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 

__attribute__((used)) static void esp_unmap_dma(struct esp *esp, struct scsi_cmnd *cmd)
{
	if (!(esp->flags & ESP_FLAG_NO_DMA_MAP))
		scsi_dma_unmap(cmd);
}