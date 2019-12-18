#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  phys_addr; scalar_t__ virt; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct sprd_uart_port {TYPE_2__ rx_dma; TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRD_UART_RX_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sprd_rx_free_buf(struct sprd_uart_port *sp)
{
	if (sp->rx_dma.virt)
		dma_free_coherent(sp->port.dev, SPRD_UART_RX_SIZE,
				  sp->rx_dma.virt, sp->rx_dma.phys_addr);

}