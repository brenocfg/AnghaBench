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
struct channel_data {int tx_status; int /*<<< orphan*/  txwaitq; int /*<<< orphan*/  wsem; int /*<<< orphan*/  txbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int chrdev_tx_done(struct channel_data *chan, int size)
{
	if (chan->tx_status) { /* Writer was interrupted */
		kfree(chan->txbuf);
		up(&chan->wsem);
	}
	chan->tx_status = 1;
	wake_up_interruptible(&chan->txwaitq);
	return 1;
}