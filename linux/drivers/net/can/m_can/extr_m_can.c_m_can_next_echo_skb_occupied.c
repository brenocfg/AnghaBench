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
struct TYPE_2__ {unsigned int echo_skb_max; int /*<<< orphan*/ * echo_skb; } ;
struct m_can_classdev {TYPE_1__ can; } ;

/* Variables and functions */
 struct m_can_classdev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int m_can_next_echo_skb_occupied(struct net_device *dev, int putidx)
{
	struct m_can_classdev *cdev = netdev_priv(dev);
	/*get wrap around for loopback skb index */
	unsigned int wrap = cdev->can.echo_skb_max;
	int next_idx;

	/* calculate next index */
	next_idx = (++putidx >= wrap ? 0 : putidx);

	/* check if occupied */
	return !!cdev->can.echo_skb[next_idx];
}