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
struct scc_channel {int /*<<< orphan*/  tx_queue; int /*<<< orphan*/ * tx_buff; int /*<<< orphan*/  init; } ;
struct net_device {scalar_t__ ml_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  init_channel (struct scc_channel*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int scc_net_open(struct net_device *dev)
{
	struct scc_channel *scc = (struct scc_channel *) dev->ml_priv;

 	if (!scc->init)
		return -EINVAL;

	scc->tx_buff = NULL;
	skb_queue_head_init(&scc->tx_queue);
 
	init_channel(scc);

	netif_start_queue(dev);
	return 0;
}