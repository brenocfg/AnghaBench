#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct link_config {int speed; int duplex; int requested_fc; scalar_t__ autoneg; unsigned char fc; } ;
struct cphy {TYPE_1__* ops; } ;
struct cmac {TYPE_3__* ops; } ;
struct TYPE_10__ {TYPE_2__* port; } ;
typedef  TYPE_4__ adapter_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* set_speed_duplex_fc ) (struct cmac*,int,int,int) ;} ;
struct TYPE_8__ {struct cmac* mac; struct link_config link_config; struct cphy* phy; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* get_link_status ) (struct cphy*,int*,int*,int*,int*) ;} ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int DUPLEX_INVALID ; 
 int PAUSE_AUTONEG ; 
 int PAUSE_RX ; 
 int PAUSE_TX ; 
 int SPEED_INVALID ; 
 int /*<<< orphan*/  stub1 (struct cphy*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  stub2 (struct cmac*,int,int,int) ; 
 int /*<<< orphan*/  t1_link_negotiated (TYPE_4__*,int,int,int,int,int) ; 

void t1_link_changed(adapter_t *adapter, int port_id)
{
	int link_ok, speed, duplex, fc;
	struct cphy *phy = adapter->port[port_id].phy;
	struct link_config *lc = &adapter->port[port_id].link_config;

	phy->ops->get_link_status(phy, &link_ok, &speed, &duplex, &fc);

	lc->speed = speed < 0 ? SPEED_INVALID : speed;
	lc->duplex = duplex < 0 ? DUPLEX_INVALID : duplex;
	if (!(lc->requested_fc & PAUSE_AUTONEG))
		fc = lc->requested_fc & (PAUSE_RX | PAUSE_TX);

	if (link_ok && speed >= 0 && lc->autoneg == AUTONEG_ENABLE) {
		/* Set MAC speed, duplex, and flow control to match PHY. */
		struct cmac *mac = adapter->port[port_id].mac;

		mac->ops->set_speed_duplex_fc(mac, speed, duplex, fc);
		lc->fc = (unsigned char)fc;
	}
	t1_link_negotiated(adapter, port_id, link_ok, speed, duplex, fc);
}