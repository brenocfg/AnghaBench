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
typedef  int /*<<< orphan*/  u32 ;
struct uart_port {struct device* dev; } ;
struct msm_dma {unsigned int count; int /*<<< orphan*/  dir; int /*<<< orphan*/  phys; int /*<<< orphan*/  enable_bit; int /*<<< orphan*/  chan; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UARTDM_DMEN ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_write (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msm_stop_dma(struct uart_port *port, struct msm_dma *dma)
{
	struct device *dev = port->dev;
	unsigned int mapped;
	u32 val;

	mapped = dma->count;
	dma->count = 0;

	dmaengine_terminate_all(dma->chan);

	/*
	 * DMA Stall happens if enqueue and flush command happens concurrently.
	 * For example before changing the baud rate/protocol configuration and
	 * sending flush command to ADM, disable the channel of UARTDM.
	 * Note: should not reset the receiver here immediately as it is not
	 * suggested to do disable/reset or reset/disable at the same time.
	 */
	val = msm_read(port, UARTDM_DMEN);
	val &= ~dma->enable_bit;
	msm_write(port, val, UARTDM_DMEN);

	if (mapped)
		dma_unmap_single(dev, dma->phys, mapped, dma->dir);
}