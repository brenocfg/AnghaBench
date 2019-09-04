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
struct vector_queue {void** skbuff_vector; int queue_depth; struct mmsghdr* mmsg_vector; int /*<<< orphan*/  dev; } ;
struct vector_private {int dummy; } ;
struct mmsghdr {int /*<<< orphan*/  msg_hdr; } ;

/* Variables and functions */
 struct vector_private* netdev_priv (int /*<<< orphan*/ ) ; 
 void* prep_skb (struct vector_private*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prep_queue_for_rx(struct vector_queue *qi)
{
	struct vector_private *vp = netdev_priv(qi->dev);
	struct mmsghdr *mmsg_vector = qi->mmsg_vector;
	void **skbuff_vector = qi->skbuff_vector;
	int i;

	if (qi->queue_depth == 0)
		return;
	for (i = 0; i < qi->queue_depth; i++) {
		/* it is OK if allocation fails - recvmmsg with NULL data in
		 * iov argument still performs an RX, just drops the packet
		 * This allows us stop faffing around with a "drop buffer"
		 */

		*skbuff_vector = prep_skb(vp, &mmsg_vector->msg_hdr);
		skbuff_vector++;
		mmsg_vector++;
	}
	qi->queue_depth = 0;
}