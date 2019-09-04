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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
struct bcom_task {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  FEC_RX_BUFFER_SIZE ; 
 int /*<<< orphan*/  bcom_queue_full (struct bcom_task*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc52xx_fec_rx_submit (struct net_device*,struct sk_buff*) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpc52xx_fec_alloc_rx_buffers(struct net_device *dev, struct bcom_task *rxtsk)
{
	struct sk_buff *skb;

	while (!bcom_queue_full(rxtsk)) {
		skb = netdev_alloc_skb(dev, FEC_RX_BUFFER_SIZE);
		if (!skb)
			return -EAGAIN;

		/* zero out the initial receive buffers to aid debugging */
		memset(skb->data, 0, FEC_RX_BUFFER_SIZE);
		mpc52xx_fec_rx_submit(dev, skb);
	}
	return 0;
}