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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct nicvf {TYPE_1__* pnicvf; } ;
struct netdev_queue {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIC_QSET_SQ_0_7_DOOR ; 
 struct netdev_queue* netdev_get_tx_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_tx_sent_queue (struct netdev_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_queue_reg_write (struct nicvf*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static inline void nicvf_sq_doorbell(struct nicvf *nic, struct sk_buff *skb,
				     int sq_num, int desc_cnt)
{
	struct netdev_queue *txq;

	txq = netdev_get_tx_queue(nic->pnicvf->netdev,
				  skb_get_queue_mapping(skb));

	netdev_tx_sent_queue(txq, skb->len);

	/* make sure all memory stores are done before ringing doorbell */
	smp_wmb();

	/* Inform HW to xmit all TSO segments */
	nicvf_queue_reg_write(nic, NIC_QSET_SQ_0_7_DOOR,
			      sq_num, desc_cnt);
}