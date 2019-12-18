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
struct cdns3_endpoint {int trb_pool_dma; } ;
struct cdns3_device {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ep_traddr; } ;

/* Variables and functions */
 int TRB_SIZE ; 
 int readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cdns3_get_dma_pos(struct cdns3_device *priv_dev,
			     struct cdns3_endpoint *priv_ep)
{
	int dma_index;

	dma_index = readl(&priv_dev->regs->ep_traddr) - priv_ep->trb_pool_dma;

	return dma_index / TRB_SIZE;
}