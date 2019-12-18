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
struct usbhs_priv {int dummy; } ;
struct usbhs_fifo {scalar_t__ rx_chan; scalar_t__ tx_chan; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ dev_of_node (struct device*) ; 
 struct device* usbhs_priv_to_dev (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhsf_dma_init_dt (struct device*,struct usbhs_fifo*,int) ; 
 int /*<<< orphan*/  usbhsf_dma_init_pdev (struct usbhs_fifo*) ; 

__attribute__((used)) static void usbhsf_dma_init(struct usbhs_priv *priv, struct usbhs_fifo *fifo,
			    int channel)
{
	struct device *dev = usbhs_priv_to_dev(priv);

	if (dev_of_node(dev))
		usbhsf_dma_init_dt(dev, fifo, channel);
	else
		usbhsf_dma_init_pdev(fifo);

	if (fifo->tx_chan || fifo->rx_chan)
		dev_dbg(dev, "enable DMAEngine (%s%s%s)\n",
			 fifo->name,
			 fifo->tx_chan ? "[TX]" : "    ",
			 fifo->rx_chan ? "[RX]" : "    ");
}