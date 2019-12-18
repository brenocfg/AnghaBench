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
struct net_device {int dummy; } ;
struct brcmf_pub {TYPE_1__** iflist; } ;
struct brcmf_bus {int state; struct brcmf_pub* drvr; } ;
typedef  enum brcmf_bus_state { ____Placeholder_brcmf_bus_state } brcmf_bus_state ;
struct TYPE_2__ {struct net_device* ndev; } ;

/* Variables and functions */
 int BRCMF_BUS_UP ; 
 int BRCMF_MAX_IFS ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

void brcmf_bus_change_state(struct brcmf_bus *bus, enum brcmf_bus_state state)
{
	struct brcmf_pub *drvr = bus->drvr;
	struct net_device *ndev;
	int ifidx;

	brcmf_dbg(TRACE, "%d -> %d\n", bus->state, state);

	if (!drvr) {
		brcmf_dbg(INFO, "ignoring transition, bus not attached yet\n");
		return;
	}

	bus->state = state;

	if (state == BRCMF_BUS_UP) {
		for (ifidx = 0; ifidx < BRCMF_MAX_IFS; ifidx++) {
			if ((drvr->iflist[ifidx]) &&
			    (drvr->iflist[ifidx]->ndev)) {
				ndev = drvr->iflist[ifidx]->ndev;
				if (netif_queue_stopped(ndev))
					netif_wake_queue(ndev);
			}
		}
	}
}