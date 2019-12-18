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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  netdev; } ;
struct nfp_net {int link_up; int /*<<< orphan*/  link_status_lock; TYPE_2__ dp; TYPE_1__* port; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_NET_CFG_STS ; 
 int NFP_NET_CFG_STS_LINK ; 
 int /*<<< orphan*/  NFP_PORT_CHANGED ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int nn_readl (struct nfp_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void nfp_net_read_link_status(struct nfp_net *nn)
{
	unsigned long flags;
	bool link_up;
	u32 sts;

	spin_lock_irqsave(&nn->link_status_lock, flags);

	sts = nn_readl(nn, NFP_NET_CFG_STS);
	link_up = !!(sts & NFP_NET_CFG_STS_LINK);

	if (nn->link_up == link_up)
		goto out;

	nn->link_up = link_up;
	if (nn->port)
		set_bit(NFP_PORT_CHANGED, &nn->port->flags);

	if (nn->link_up) {
		netif_carrier_on(nn->dp.netdev);
		netdev_info(nn->dp.netdev, "NIC Link is Up\n");
	} else {
		netif_carrier_off(nn->dp.netdev);
		netdev_info(nn->dp.netdev, "NIC Link is Down\n");
	}
out:
	spin_unlock_irqrestore(&nn->link_status_lock, flags);
}