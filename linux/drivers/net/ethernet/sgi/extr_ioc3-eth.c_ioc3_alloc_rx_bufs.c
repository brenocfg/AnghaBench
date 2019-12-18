#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct net_device {int dummy; } ;
struct ioc3_private {int rx_pi; scalar_t__ rx_ci; int /*<<< orphan*/ * rxr; int /*<<< orphan*/ * rx_skbs; } ;
struct ioc3_erxbuf {scalar_t__ w0; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PCI64_ATTR_BAR ; 
 int RX_BUFFS ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 scalar_t__ ioc3_alloc_skb (struct ioc3_private*,int /*<<< orphan*/ *,struct ioc3_erxbuf**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioc3_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ioc3_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ioc3_alloc_rx_bufs(struct net_device *dev)
{
	struct ioc3_private *ip = netdev_priv(dev);
	struct ioc3_erxbuf *rxb;
	dma_addr_t d;
	int i;

	/* Now the rx buffers.  The RX ring may be larger but
	 * we only allocate 16 buffers for now.  Need to tune
	 * this for performance and memory later.
	 */
	for (i = 0; i < RX_BUFFS; i++) {
		if (ioc3_alloc_skb(ip, &ip->rx_skbs[i], &rxb, &d))
			return -ENOMEM;

		rxb->w0 = 0;	/* Clear valid flag */
		ip->rxr[i] = cpu_to_be64(ioc3_map(d, PCI64_ATTR_BAR));
	}
	ip->rx_ci = 0;
	ip->rx_pi = RX_BUFFS;

	return 0;
}