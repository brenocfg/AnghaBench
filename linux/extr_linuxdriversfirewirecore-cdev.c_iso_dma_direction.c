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
struct fw_iso_context {scalar_t__ type; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 scalar_t__ FW_ISO_CONTEXT_TRANSMIT ; 

__attribute__((used)) static enum dma_data_direction iso_dma_direction(struct fw_iso_context *context)
{
		if (context->type == FW_ISO_CONTEXT_TRANSMIT)
			return DMA_TO_DEVICE;
		else
			return DMA_FROM_DEVICE;
}