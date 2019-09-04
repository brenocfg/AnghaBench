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
struct ucc_geth_private {TYPE_1__* ug_regs; struct net_device* ndev; } ;
struct net_device {int /*<<< orphan*/ * dev_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  macstnaddr2; int /*<<< orphan*/  macstnaddr1; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMM_DIR_RX_AND_TX ; 
 int adjust_enet_interface (struct ucc_geth_private*) ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  init_mac_station_addr_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_err (struct ucc_geth_private*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int ucc_geth_startup (struct ucc_geth_private*) ; 
 int /*<<< orphan*/  ucc_geth_stop (struct ucc_geth_private*) ; 
 int ucc_struct_init (struct ucc_geth_private*) ; 
 int ugeth_enable (struct ucc_geth_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ucc_geth_init_mac(struct ucc_geth_private *ugeth)
{
	struct net_device *dev = ugeth->ndev;
	int err;

	err = ucc_struct_init(ugeth);
	if (err) {
		netif_err(ugeth, ifup, dev, "Cannot configure internal struct, aborting\n");
		goto err;
	}

	err = ucc_geth_startup(ugeth);
	if (err) {
		netif_err(ugeth, ifup, dev, "Cannot configure net device, aborting\n");
		goto err;
	}

	err = adjust_enet_interface(ugeth);
	if (err) {
		netif_err(ugeth, ifup, dev, "Cannot configure net device, aborting\n");
		goto err;
	}

	/*       Set MACSTNADDR1, MACSTNADDR2                */
	/* For more details see the hardware spec.           */
	init_mac_station_addr_regs(dev->dev_addr[0],
				   dev->dev_addr[1],
				   dev->dev_addr[2],
				   dev->dev_addr[3],
				   dev->dev_addr[4],
				   dev->dev_addr[5],
				   &ugeth->ug_regs->macstnaddr1,
				   &ugeth->ug_regs->macstnaddr2);

	err = ugeth_enable(ugeth, COMM_DIR_RX_AND_TX);
	if (err) {
		netif_err(ugeth, ifup, dev, "Cannot enable net device, aborting\n");
		goto err;
	}

	return 0;
err:
	ucc_geth_stop(ugeth);
	return err;
}