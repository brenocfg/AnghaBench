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
struct TYPE_2__ {int use_frag; int /*<<< orphan*/  use_fcs; int /*<<< orphan*/  use_stx; int /*<<< orphan*/  link_select; } ;
struct ser_device {struct net_device* dev; TYPE_1__ common; int /*<<< orphan*/  head; } ;
struct net_device {int flags; int needs_free_netdev; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  mtu; int /*<<< orphan*/  type; int /*<<< orphan*/ * netdev_ops; scalar_t__ features; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_CAIF ; 
 int /*<<< orphan*/  CAIF_LINK_LOW_LATENCY ; 
 int /*<<< orphan*/  CAIF_MAX_MTU ; 
 int IFF_NOARP ; 
 int /*<<< orphan*/  IFF_NO_QUEUE ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  netdev_ops ; 
 struct ser_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ser_use_fcs ; 
 int /*<<< orphan*/  ser_use_stx ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void caifdev_setup(struct net_device *dev)
{
	struct ser_device *serdev = netdev_priv(dev);

	dev->features = 0;
	dev->netdev_ops = &netdev_ops;
	dev->type = ARPHRD_CAIF;
	dev->flags = IFF_POINTOPOINT | IFF_NOARP;
	dev->mtu = CAIF_MAX_MTU;
	dev->priv_flags |= IFF_NO_QUEUE;
	dev->needs_free_netdev = true;
	skb_queue_head_init(&serdev->head);
	serdev->common.link_select = CAIF_LINK_LOW_LATENCY;
	serdev->common.use_frag = true;
	serdev->common.use_stx = ser_use_stx;
	serdev->common.use_fcs = ser_use_fcs;
	serdev->dev = dev;
}