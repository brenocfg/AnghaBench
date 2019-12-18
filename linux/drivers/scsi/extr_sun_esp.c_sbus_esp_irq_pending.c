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
struct esp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CSR ; 
 int DMA_HNDL_ERROR ; 
 int DMA_HNDL_INTR ; 
 int dma_read32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sbus_esp_irq_pending(struct esp *esp)
{
	if (dma_read32(DMA_CSR) & (DMA_HNDL_INTR | DMA_HNDL_ERROR))
		return 1;
	return 0;
}