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
struct sbp_session {scalar_t__ generation; int node_id; int reconnect_hold; int /*<<< orphan*/  lock; scalar_t__ reconnect_expires; int /*<<< orphan*/  guid; TYPE_1__* card; } ;
struct TYPE_2__ {scalar_t__ generation; int /*<<< orphan*/  lock; int /*<<< orphan*/ * local_node; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  fw_card_put (TYPE_1__*) ; 
 scalar_t__ get_jiffies_64 () ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void session_check_for_reset(struct sbp_session *sess)
{
	bool card_valid = false;

	spin_lock_bh(&sess->lock);

	if (sess->card) {
		spin_lock_irq(&sess->card->lock);
		card_valid = (sess->card->local_node != NULL);
		spin_unlock_irq(&sess->card->lock);

		if (!card_valid) {
			fw_card_put(sess->card);
			sess->card = NULL;
		}
	}

	if (!card_valid || (sess->generation != sess->card->generation)) {
		pr_info("Waiting for reconnect from node: %016llx\n",
				sess->guid);

		sess->node_id = -1;
		sess->reconnect_expires = get_jiffies_64() +
			((sess->reconnect_hold + 1) * HZ);
	}

	spin_unlock_bh(&sess->lock);
}