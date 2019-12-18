#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct device* dev; } ;
struct uart_8250_port {struct uart_8250_dma* dma; TYPE_1__ port; } ;
struct TYPE_7__ {int dst_maxburst; } ;
struct TYPE_6__ {int src_maxburst; } ;
struct uart_8250_dma {struct hsu_dma_slave* tx_param; struct hsu_dma_slave* rx_param; int /*<<< orphan*/  fn; TYPE_3__ txconf; TYPE_2__ rxconf; } ;
struct mid8250 {int dma_index; TYPE_4__* dma_dev; struct uart_8250_dma dma; } ;
struct hsu_dma_slave {int chan_id; int /*<<< orphan*/ * dma_dev; } ;
struct device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct hsu_dma_slave* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mid8250_dma_filter ; 

__attribute__((used)) static int mid8250_dma_setup(struct mid8250 *mid, struct uart_8250_port *port)
{
	struct uart_8250_dma *dma = &mid->dma;
	struct device *dev = port->port.dev;
	struct hsu_dma_slave *rx_param;
	struct hsu_dma_slave *tx_param;

	if (!mid->dma_dev)
		return 0;

	rx_param = devm_kzalloc(dev, sizeof(*rx_param), GFP_KERNEL);
	if (!rx_param)
		return -ENOMEM;

	tx_param = devm_kzalloc(dev, sizeof(*tx_param), GFP_KERNEL);
	if (!tx_param)
		return -ENOMEM;

	rx_param->chan_id = mid->dma_index * 2 + 1;
	tx_param->chan_id = mid->dma_index * 2;

	dma->rxconf.src_maxburst = 64;
	dma->txconf.dst_maxburst = 64;

	rx_param->dma_dev = &mid->dma_dev->dev;
	tx_param->dma_dev = &mid->dma_dev->dev;

	dma->fn = mid8250_dma_filter;
	dma->rx_param = rx_param;
	dma->tx_param = tx_param;

	port->dma = dma;
	return 0;
}