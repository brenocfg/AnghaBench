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
struct cdns3_endpoint {int wa1_trb_index; } ;
struct cdns3_device {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ep_cmd; } ;

/* Variables and functions */
 int EP_CMD_DRDY ; 
 int cdns3_get_dma_pos (struct cdns3_device*,struct cdns3_endpoint*) ; 
 int /*<<< orphan*/  cdns3_wa1_restore_cycle_bit (struct cdns3_endpoint*) ; 
 int readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cdns3_wa1_tray_restore_cycle_bit(struct cdns3_device *priv_dev,
					     struct cdns3_endpoint *priv_ep)
{
	int dma_index;
	u32 doorbell;

	doorbell = !!(readl(&priv_dev->regs->ep_cmd) & EP_CMD_DRDY);
	dma_index = cdns3_get_dma_pos(priv_dev, priv_ep);

	if (!doorbell || dma_index != priv_ep->wa1_trb_index)
		cdns3_wa1_restore_cycle_bit(priv_ep);
}