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
struct sk_buff {int dummy; } ;
struct sis190_private {scalar_t__ RxDescRing; int /*<<< orphan*/  Rx_skbuff; int /*<<< orphan*/  Tx_skbuff; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int NUM_RX_DESC ; 
 int NUM_TX_DESC ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 struct sis190_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sis190_init_ring_indexes (struct sis190_private*) ; 
 int /*<<< orphan*/  sis190_mark_as_last_descriptor (scalar_t__) ; 
 int /*<<< orphan*/  sis190_rx_clear (struct sis190_private*) ; 
 int sis190_rx_fill (struct sis190_private*,struct net_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sis190_init_ring(struct net_device *dev)
{
	struct sis190_private *tp = netdev_priv(dev);

	sis190_init_ring_indexes(tp);

	memset(tp->Tx_skbuff, 0x0, NUM_TX_DESC * sizeof(struct sk_buff *));
	memset(tp->Rx_skbuff, 0x0, NUM_RX_DESC * sizeof(struct sk_buff *));

	if (sis190_rx_fill(tp, dev, 0, NUM_RX_DESC) != NUM_RX_DESC)
		goto err_rx_clear;

	sis190_mark_as_last_descriptor(tp->RxDescRing + NUM_RX_DESC - 1);

	return 0;

err_rx_clear:
	sis190_rx_clear(tp);
	return -ENOMEM;
}