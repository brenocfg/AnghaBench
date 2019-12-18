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
struct uart_port {int dummy; } ;
struct msm_dma {scalar_t__ chan; } ;
struct msm_port {int imr; struct msm_dma rx_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_IMR ; 
 int UART_IMR_RXLEV ; 
 int UART_IMR_RXSTALE ; 
 struct msm_port* UART_TO_MSM (struct uart_port*) ; 
 int /*<<< orphan*/  msm_stop_dma (struct uart_port*,struct msm_dma*) ; 
 int /*<<< orphan*/  msm_write (struct uart_port*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msm_stop_rx(struct uart_port *port)
{
	struct msm_port *msm_port = UART_TO_MSM(port);
	struct msm_dma *dma = &msm_port->rx_dma;

	msm_port->imr &= ~(UART_IMR_RXLEV | UART_IMR_RXSTALE);
	msm_write(port, msm_port->imr, UART_IMR);

	if (dma->chan)
		msm_stop_dma(port, dma);
}