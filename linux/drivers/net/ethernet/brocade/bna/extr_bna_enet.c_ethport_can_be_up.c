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
struct bna_ethport {int flags; TYPE_2__* bna; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {TYPE_1__ enet; } ;

/* Variables and functions */
 scalar_t__ BNA_ENET_T_REGULAR ; 
 int BNA_ETHPORT_F_ADMIN_UP ; 
 int BNA_ETHPORT_F_PORT_ENABLED ; 
 int BNA_ETHPORT_F_RX_STARTED ; 

__attribute__((used)) static inline int
ethport_can_be_up(struct bna_ethport *ethport)
{
	int ready = 0;
	if (ethport->bna->enet.type == BNA_ENET_T_REGULAR)
		ready = ((ethport->flags & BNA_ETHPORT_F_ADMIN_UP) &&
			 (ethport->flags & BNA_ETHPORT_F_RX_STARTED) &&
			 (ethport->flags & BNA_ETHPORT_F_PORT_ENABLED));
	else
		ready = ((ethport->flags & BNA_ETHPORT_F_ADMIN_UP) &&
			 (ethport->flags & BNA_ETHPORT_F_RX_STARTED) &&
			 !(ethport->flags & BNA_ETHPORT_F_PORT_ENABLED));
	return ready;
}