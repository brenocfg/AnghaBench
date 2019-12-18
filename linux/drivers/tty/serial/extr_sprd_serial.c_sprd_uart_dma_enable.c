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
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRD_CTL1 ; 
 int /*<<< orphan*/  SPRD_DMA_EN ; 
 int /*<<< orphan*/  serial_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sprd_uart_dma_enable(struct uart_port *port, bool enable)
{
	u32 val = serial_in(port, SPRD_CTL1);

	if (enable)
		val |= SPRD_DMA_EN;
	else
		val &= ~SPRD_DMA_EN;

	serial_out(port, SPRD_CTL1, val);
}