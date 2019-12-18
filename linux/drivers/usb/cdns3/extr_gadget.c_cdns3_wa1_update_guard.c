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
struct cdns3_trb {int dummy; } ;
struct cdns3_endpoint {int wa1_set; int /*<<< orphan*/  enqueue; int /*<<< orphan*/  wa1_trb_index; struct cdns3_trb* wa1_trb; scalar_t__ pcs; int /*<<< orphan*/  wa1_cycle_bit; struct cdns3_device* cdns3_dev; } ;
struct cdns3_device {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ep_cmd; } ;

/* Variables and functions */
 int EP_CMD_DRDY ; 
 int /*<<< orphan*/  TRB_CYCLE ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_cdns3_wa1 (struct cdns3_endpoint*,char*) ; 

__attribute__((used)) static int cdns3_wa1_update_guard(struct cdns3_endpoint *priv_ep,
				  struct cdns3_trb *trb)
{
	struct cdns3_device *priv_dev = priv_ep->cdns3_dev;

	if (!priv_ep->wa1_set) {
		u32 doorbell;

		doorbell = !!(readl(&priv_dev->regs->ep_cmd) & EP_CMD_DRDY);

		if (doorbell) {
			priv_ep->wa1_cycle_bit = priv_ep->pcs ? TRB_CYCLE : 0;
			priv_ep->wa1_set = 1;
			priv_ep->wa1_trb = trb;
			priv_ep->wa1_trb_index = priv_ep->enqueue;
			trace_cdns3_wa1(priv_ep, "set guard");
			return 0;
		}
	}
	return 1;
}