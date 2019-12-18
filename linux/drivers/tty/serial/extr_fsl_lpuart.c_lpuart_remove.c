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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  line; } ;
struct lpuart_port {scalar_t__ dma_rx_chan; scalar_t__ dma_tx_chan; TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 int /*<<< orphan*/  fsl_lpuart_ida ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpuart_disable_clks (struct lpuart_port*) ; 
 int /*<<< orphan*/  lpuart_reg ; 
 struct lpuart_port* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int lpuart_remove(struct platform_device *pdev)
{
	struct lpuart_port *sport = platform_get_drvdata(pdev);

	uart_remove_one_port(&lpuart_reg, &sport->port);

	ida_simple_remove(&fsl_lpuart_ida, sport->port.line);

	lpuart_disable_clks(sport);

	if (sport->dma_tx_chan)
		dma_release_channel(sport->dma_tx_chan);

	if (sport->dma_rx_chan)
		dma_release_channel(sport->dma_rx_chan);

	return 0;
}