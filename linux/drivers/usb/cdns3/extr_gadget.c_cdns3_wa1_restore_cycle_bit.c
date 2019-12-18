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
struct cdns3_endpoint {int wa1_trb_index; TYPE_1__* wa1_trb; scalar_t__ wa1_cycle_bit; scalar_t__ wa1_set; } ;
struct TYPE_2__ {int control; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_cdns3_wa1 (struct cdns3_endpoint*,char*) ; 

void cdns3_wa1_restore_cycle_bit(struct cdns3_endpoint *priv_ep)
{
	/* Work around for stale data address in TRB*/
	if (priv_ep->wa1_set) {
		trace_cdns3_wa1(priv_ep, "restore cycle bit");

		priv_ep->wa1_set = 0;
		priv_ep->wa1_trb_index = 0xFFFF;
		if (priv_ep->wa1_cycle_bit) {
			priv_ep->wa1_trb->control =
				priv_ep->wa1_trb->control | 0x1;
		} else {
			priv_ep->wa1_trb->control =
				priv_ep->wa1_trb->control & ~0x1;
		}
	}
}