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
struct hsc_channel {int /*<<< orphan*/  tx_msgs_queue; int /*<<< orphan*/  rx_msgs_queue; int /*<<< orphan*/  free_msgs_list; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_wait; int /*<<< orphan*/  rx_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hsc_channel_init(struct hsc_channel *channel)
{
	init_waitqueue_head(&channel->rx_wait);
	init_waitqueue_head(&channel->tx_wait);
	spin_lock_init(&channel->lock);
	INIT_LIST_HEAD(&channel->free_msgs_list);
	INIT_LIST_HEAD(&channel->rx_msgs_queue);
	INIT_LIST_HEAD(&channel->tx_msgs_queue);
}