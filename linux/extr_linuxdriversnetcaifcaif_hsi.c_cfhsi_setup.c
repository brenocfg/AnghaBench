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
struct net_device {int flags; int needs_free_netdev; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  mtu; int /*<<< orphan*/  type; scalar_t__ features; } ;
struct TYPE_2__ {int use_frag; int use_stx; int use_fcs; int /*<<< orphan*/  link_select; } ;
struct cfhsi {int /*<<< orphan*/  cfg; struct net_device* ndev; TYPE_1__ cfdev; int /*<<< orphan*/ * qhead; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_CAIF ; 
 int /*<<< orphan*/  CAIF_LINK_HIGH_BANDW ; 
 int /*<<< orphan*/  CFHSI_MAX_CAIF_FRAME_SZ ; 
 int CFHSI_PRIO_LAST ; 
 int IFF_NOARP ; 
 int /*<<< orphan*/  IFF_NO_QUEUE ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  cfhsi_netdevops ; 
 int /*<<< orphan*/  hsi_default_config ; 
 struct cfhsi* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cfhsi_setup(struct net_device *dev)
{
	int i;
	struct cfhsi *cfhsi = netdev_priv(dev);
	dev->features = 0;
	dev->type = ARPHRD_CAIF;
	dev->flags = IFF_POINTOPOINT | IFF_NOARP;
	dev->mtu = CFHSI_MAX_CAIF_FRAME_SZ;
	dev->priv_flags |= IFF_NO_QUEUE;
	dev->needs_free_netdev = true;
	dev->netdev_ops = &cfhsi_netdevops;
	for (i = 0; i < CFHSI_PRIO_LAST; ++i)
		skb_queue_head_init(&cfhsi->qhead[i]);
	cfhsi->cfdev.link_select = CAIF_LINK_HIGH_BANDW;
	cfhsi->cfdev.use_frag = false;
	cfhsi->cfdev.use_stx = false;
	cfhsi->cfdev.use_fcs = false;
	cfhsi->ndev = dev;
	cfhsi->cfg = hsi_default_config;
}