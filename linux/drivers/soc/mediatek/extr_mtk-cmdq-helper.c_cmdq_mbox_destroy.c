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
struct cmdq_client {scalar_t__ timeout_ms; int /*<<< orphan*/  chan; int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 scalar_t__ CMDQ_NO_TIMEOUT ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct cmdq_client*) ; 
 int /*<<< orphan*/  mbox_free_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void cmdq_mbox_destroy(struct cmdq_client *client)
{
	if (client->timeout_ms != CMDQ_NO_TIMEOUT) {
		spin_lock(&client->lock);
		del_timer_sync(&client->timer);
		spin_unlock(&client->lock);
	}
	mbox_free_channel(client->chan);
	kfree(client);
}