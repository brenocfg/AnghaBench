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

/* Variables and functions */
 int /*<<< orphan*/  HW_EVENT_MAPLE_DMA ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  maple_dma_interrupt ; 
 int /*<<< orphan*/  maple_unsupported_device ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int maple_set_dma_interrupt_handler(void)
{
	return request_irq(HW_EVENT_MAPLE_DMA, maple_dma_interrupt,
		IRQF_SHARED, "maple bus DMA", &maple_unsupported_device);
}