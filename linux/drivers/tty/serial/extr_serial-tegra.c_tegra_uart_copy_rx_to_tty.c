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
struct tty_port {int dummy; } ;
struct TYPE_3__ {unsigned int rx; } ;
struct TYPE_4__ {int ignore_status_mask; int /*<<< orphan*/  dev; TYPE_1__ icount; } ;
struct tegra_uart_port {int /*<<< orphan*/  rx_dma_buf_phys; TYPE_2__ uport; scalar_t__ rx_dma_buf_virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  TEGRA_UART_RX_DMA_BUFFER_SIZE ; 
 int UART_LSR_DR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tty_insert_flip_string (struct tty_port*,unsigned char*,unsigned int) ; 

__attribute__((used)) static void tegra_uart_copy_rx_to_tty(struct tegra_uart_port *tup,
				      struct tty_port *tty,
				      unsigned int count)
{
	int copied;

	/* If count is zero, then there is no data to be copied */
	if (!count)
		return;

	tup->uport.icount.rx += count;
	if (!tty) {
		dev_err(tup->uport.dev, "No tty port\n");
		return;
	}

	if (tup->uport.ignore_status_mask & UART_LSR_DR)
		return;

	dma_sync_single_for_cpu(tup->uport.dev, tup->rx_dma_buf_phys,
				TEGRA_UART_RX_DMA_BUFFER_SIZE, DMA_FROM_DEVICE);
	copied = tty_insert_flip_string(tty,
			((unsigned char *)(tup->rx_dma_buf_virt)), count);
	if (copied != count) {
		WARN_ON(1);
		dev_err(tup->uport.dev, "RxData copy to tty layer failed\n");
	}
	dma_sync_single_for_device(tup->uport.dev, tup->rx_dma_buf_phys,
				TEGRA_UART_RX_DMA_BUFFER_SIZE, DMA_TO_DEVICE);
}