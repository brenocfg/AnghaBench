#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vector_queue {int queue_depth; int max_depth; int tail; int /*<<< orphan*/  tail_lock; TYPE_4__* dev; struct sk_buff** skbuff_vector; int /*<<< orphan*/  head_lock; struct mmsghdr* mmsg_vector; } ;
struct vector_private {TYPE_2__* fds; } ;
struct sk_buff {int len; } ;
struct TYPE_6__ {int msg_iovlen; int /*<<< orphan*/  msg_namelen; int /*<<< orphan*/  msg_name; int /*<<< orphan*/  msg_iov; } ;
struct mmsghdr {TYPE_1__ msg_hdr; } ;
struct TYPE_8__ {int /*<<< orphan*/  tx_dropped; } ;
struct TYPE_9__ {TYPE_3__ stats; } ;
struct TYPE_7__ {int /*<<< orphan*/  remote_addr_size; int /*<<< orphan*/  remote_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_completed_queue (TYPE_4__*,int,int) ; 
 struct vector_private* netdev_priv (TYPE_4__*) ; 
 int prep_msg (struct vector_private*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int vector_advancetail (struct vector_queue*,int) ; 

__attribute__((used)) static int vector_enqueue(struct vector_queue *qi, struct sk_buff *skb)
{
	struct vector_private *vp = netdev_priv(qi->dev);
	int queue_depth;
	int packet_len;
	struct mmsghdr *mmsg_vector = qi->mmsg_vector;
	int iov_count;

	spin_lock(&qi->tail_lock);
	spin_lock(&qi->head_lock);
	queue_depth = qi->queue_depth;
	spin_unlock(&qi->head_lock);

	if (skb)
		packet_len = skb->len;

	if (queue_depth < qi->max_depth) {

		*(qi->skbuff_vector + qi->tail) = skb;
		mmsg_vector += qi->tail;
		iov_count = prep_msg(
			vp,
			skb,
			mmsg_vector->msg_hdr.msg_iov
		);
		if (iov_count < 1)
			goto drop;
		mmsg_vector->msg_hdr.msg_iovlen = iov_count;
		mmsg_vector->msg_hdr.msg_name = vp->fds->remote_addr;
		mmsg_vector->msg_hdr.msg_namelen = vp->fds->remote_addr_size;
		queue_depth = vector_advancetail(qi, 1);
	} else
		goto drop;
	spin_unlock(&qi->tail_lock);
	return queue_depth;
drop:
	qi->dev->stats.tx_dropped++;
	if (skb != NULL) {
		packet_len = skb->len;
		dev_consume_skb_any(skb);
		netdev_completed_queue(qi->dev, 1, packet_len);
	}
	spin_unlock(&qi->tail_lock);
	return queue_depth;
}