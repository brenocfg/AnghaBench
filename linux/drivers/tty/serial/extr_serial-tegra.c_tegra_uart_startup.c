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
struct uart_port {int irq; int /*<<< orphan*/  dev; } ;
struct tegra_uart_port {int /*<<< orphan*/  use_tx_pio; int /*<<< orphan*/  use_rx_pio; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tegra_uart_port*) ; 
 int tegra_uart_dma_channel_allocate (struct tegra_uart_port*,int) ; 
 int /*<<< orphan*/  tegra_uart_dma_channel_free (struct tegra_uart_port*,int) ; 
 int tegra_uart_hw_init (struct tegra_uart_port*) ; 
 int /*<<< orphan*/  tegra_uart_isr ; 
 struct tegra_uart_port* to_tegra_uport (struct uart_port*) ; 

__attribute__((used)) static int tegra_uart_startup(struct uart_port *u)
{
	struct tegra_uart_port *tup = to_tegra_uport(u);
	int ret;

	if (!tup->use_tx_pio) {
		ret = tegra_uart_dma_channel_allocate(tup, false);
		if (ret < 0) {
			dev_err(u->dev, "Tx Dma allocation failed, err = %d\n",
				ret);
			return ret;
		}
	}

	if (!tup->use_rx_pio) {
		ret = tegra_uart_dma_channel_allocate(tup, true);
		if (ret < 0) {
			dev_err(u->dev, "Rx Dma allocation failed, err = %d\n",
				ret);
			goto fail_rx_dma;
		}
	}

	ret = tegra_uart_hw_init(tup);
	if (ret < 0) {
		dev_err(u->dev, "Uart HW init failed, err = %d\n", ret);
		goto fail_hw_init;
	}

	ret = request_irq(u->irq, tegra_uart_isr, 0,
				dev_name(u->dev), tup);
	if (ret < 0) {
		dev_err(u->dev, "Failed to register ISR for IRQ %d\n", u->irq);
		goto fail_hw_init;
	}
	return 0;

fail_hw_init:
	if (!tup->use_rx_pio)
		tegra_uart_dma_channel_free(tup, true);
fail_rx_dma:
	if (!tup->use_tx_pio)
		tegra_uart_dma_channel_free(tup, false);
	return ret;
}