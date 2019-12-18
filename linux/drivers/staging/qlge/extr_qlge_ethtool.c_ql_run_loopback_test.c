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
struct sk_buff {scalar_t__ queue_mapping; } ;
struct ql_adapter {int /*<<< orphan*/  lb_count; int /*<<< orphan*/ * rx_ring; int /*<<< orphan*/  ndev; } ;
typedef  scalar_t__ netdev_tx_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int EPIPE ; 
 scalar_t__ NETDEV_TX_OK ; 
 unsigned int SMALL_BUF_MAP_SIZE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct sk_buff* netdev_alloc_skb (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ql_clean_lb_rx_ring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ql_create_lb_frame (struct sk_buff*,unsigned int) ; 
 scalar_t__ ql_lb_send (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static int ql_run_loopback_test(struct ql_adapter *qdev)
{
	int i;
	netdev_tx_t rc;
	struct sk_buff *skb;
	unsigned int size = SMALL_BUF_MAP_SIZE;

	for (i = 0; i < 64; i++) {
		skb = netdev_alloc_skb(qdev->ndev, size);
		if (!skb)
			return -ENOMEM;

		skb->queue_mapping = 0;
		skb_put(skb, size);
		ql_create_lb_frame(skb, size);
		rc = ql_lb_send(skb, qdev->ndev);
		if (rc != NETDEV_TX_OK)
			return -EPIPE;
		atomic_inc(&qdev->lb_count);
	}
	/* Give queue time to settle before testing results. */
	msleep(2);
	ql_clean_lb_rx_ring(&qdev->rx_ring[0], 128);
	return atomic_read(&qdev->lb_count) ? -EIO : 0;
}