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
typedef  int u32 ;
struct musb {int /*<<< orphan*/  ctrl_base; } ;
struct TYPE_2__ {struct musb* musb; } ;
struct cppi41_dma_controller {int tx_mode; TYPE_1__ controller; } ;
struct cppi41_dma_channel {int port_num; int /*<<< orphan*/  is_tx; struct cppi41_dma_controller* controller; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA8XX_USB_MODE ; 
 int /*<<< orphan*/  musb_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void da8xx_set_dma_mode(struct cppi41_dma_channel *cppi41_channel,
		unsigned int mode)
{
	struct cppi41_dma_controller *controller = cppi41_channel->controller;
	struct musb *musb = controller->controller.musb;
	unsigned int shift;
	u32 port;
	u32 new_mode;
	u32 old_mode;

	old_mode = controller->tx_mode;
	port = cppi41_channel->port_num;

	shift = (port - 1) * 4;
	if (!cppi41_channel->is_tx)
		shift += 16;
	new_mode = old_mode & ~(3 << shift);
	new_mode |= mode << shift;

	if (new_mode == old_mode)
		return;
	controller->tx_mode = new_mode;
	musb_writel(musb->ctrl_base, DA8XX_USB_MODE, new_mode);
}