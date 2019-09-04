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
struct port_info {int /*<<< orphan*/  link_config; int /*<<< orphan*/  phy; TYPE_2__* dev; struct cmac* mac; } ;
struct cmac {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* enable ) (struct cmac*,int) ;int /*<<< orphan*/  (* macaddress_set ) (struct cmac*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* reset ) (struct cmac*) ;} ;

/* Variables and functions */
 int MAC_DIRECTION_RX ; 
 int MAC_DIRECTION_TX ; 
 int /*<<< orphan*/  stub1 (struct cmac*) ; 
 int /*<<< orphan*/  stub2 (struct cmac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct cmac*,int) ; 
 int /*<<< orphan*/  t1_link_start (int /*<<< orphan*/ ,struct cmac*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t1_set_rxmode (TYPE_2__*) ; 

__attribute__((used)) static void link_start(struct port_info *p)
{
	struct cmac *mac = p->mac;

	mac->ops->reset(mac);
	if (mac->ops->macaddress_set)
		mac->ops->macaddress_set(mac, p->dev->dev_addr);
	t1_set_rxmode(p->dev);
	t1_link_start(p->phy, mac, &p->link_config);
	mac->ops->enable(mac, MAC_DIRECTION_RX | MAC_DIRECTION_TX);
}