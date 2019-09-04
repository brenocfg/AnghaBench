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
struct sk_buff {scalar_t__* cb; } ;
struct fmdev {int /*<<< orphan*/  rx_task; int /*<<< orphan*/  rx_q; } ;

/* Variables and functions */
 long EFAULT ; 
 long EINVAL ; 
 scalar_t__ FM_PKT_LOGICAL_CHAN_NUMBER ; 
 int /*<<< orphan*/  fmerr (char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long fm_st_receive(void *arg, struct sk_buff *skb)
{
	struct fmdev *fmdev;

	fmdev = (struct fmdev *)arg;

	if (skb == NULL) {
		fmerr("Invalid SKB received from ST\n");
		return -EFAULT;
	}

	if (skb->cb[0] != FM_PKT_LOGICAL_CHAN_NUMBER) {
		fmerr("Received SKB (%p) is not FM Channel 8 pkt\n", skb);
		return -EINVAL;
	}

	memcpy(skb_push(skb, 1), &skb->cb[0], 1);
	skb_queue_tail(&fmdev->rx_q, skb);
	tasklet_schedule(&fmdev->rx_task);

	return 0;
}