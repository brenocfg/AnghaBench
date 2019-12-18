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
struct qeth_channel {scalar_t__ state; int /*<<< orphan*/  ccwdev; } ;
struct qeth_card {int /*<<< orphan*/  wait_q; } ;

/* Variables and functions */
 scalar_t__ CH_STATE_DOWN ; 
 scalar_t__ CH_STATE_STOPPED ; 
 int ERESTARTSYS ; 
 int ETIME ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_CLEAR_CHANNEL_PARM ; 
 int /*<<< orphan*/  QETH_TIMEOUT ; 
 int ccw_device_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_clear_channel(struct qeth_card *card,
			      struct qeth_channel *channel)
{
	int rc;

	QETH_CARD_TEXT(card, 3, "clearch");
	spin_lock_irq(get_ccwdev_lock(channel->ccwdev));
	rc = ccw_device_clear(channel->ccwdev, QETH_CLEAR_CHANNEL_PARM);
	spin_unlock_irq(get_ccwdev_lock(channel->ccwdev));

	if (rc)
		return rc;
	rc = wait_event_interruptible_timeout(card->wait_q,
			channel->state == CH_STATE_STOPPED, QETH_TIMEOUT);
	if (rc == -ERESTARTSYS)
		return rc;
	if (channel->state != CH_STATE_STOPPED)
		return -ETIME;
	channel->state = CH_STATE_DOWN;
	return 0;
}