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
struct timer_list {int dummy; } ;
struct altera_mbox {int /*<<< orphan*/  rxpoll_timer; int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBOX_POLLING_MS ; 
 int /*<<< orphan*/  altera_mbox_rx_data (int /*<<< orphan*/ ) ; 
 struct altera_mbox* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 struct altera_mbox* mbox ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxpoll_timer ; 

__attribute__((used)) static void altera_mbox_poll_rx(struct timer_list *t)
{
	struct altera_mbox *mbox = from_timer(mbox, t, rxpoll_timer);

	altera_mbox_rx_data(mbox->chan);

	mod_timer(&mbox->rxpoll_timer,
		  jiffies + msecs_to_jiffies(MBOX_POLLING_MS));
}