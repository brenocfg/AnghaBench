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
struct usbnet {int /*<<< orphan*/  wait; int /*<<< orphan*/  net; int /*<<< orphan*/  done; int /*<<< orphan*/  txq; int /*<<< orphan*/  rxq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  ifdown ; 
 int /*<<< orphan*/  netif_dbg (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int unlink_urbs (struct usbnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wait_skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usbnet_terminate_urbs(struct usbnet *dev)
{
	DECLARE_WAITQUEUE(wait, current);
	int temp;

	/* ensure there are no more active urbs */
	add_wait_queue(&dev->wait, &wait);
	set_current_state(TASK_UNINTERRUPTIBLE);
	temp = unlink_urbs(dev, &dev->txq) +
		unlink_urbs(dev, &dev->rxq);

	/* maybe wait for deletions to finish. */
	wait_skb_queue_empty(&dev->rxq);
	wait_skb_queue_empty(&dev->txq);
	wait_skb_queue_empty(&dev->done);
	netif_dbg(dev, ifdown, dev->net,
		  "waited for %d urb completions\n", temp);
	set_current_state(TASK_RUNNING);
	remove_wait_queue(&dev->wait, &wait);
}