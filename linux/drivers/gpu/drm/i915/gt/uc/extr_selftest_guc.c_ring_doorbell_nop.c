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
struct intel_guc_client {int use_nop_wqi; int /*<<< orphan*/  doorbell_id; int /*<<< orphan*/  wq_lock; } ;
struct guc_process_desc {scalar_t__ wq_status; int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ WQ_STATUS_ACTIVE ; 
 struct guc_process_desc* __get_process_desc (struct intel_guc_client*) ; 
 int /*<<< orphan*/  guc_ring_doorbell (struct intel_guc_client*) ; 
 int /*<<< orphan*/  guc_wq_item_append (struct intel_guc_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int wait_for (int,int) ; 

__attribute__((used)) static int ring_doorbell_nop(struct intel_guc_client *client)
{
	struct guc_process_desc *desc = __get_process_desc(client);
	int err;

	client->use_nop_wqi = true;

	spin_lock_irq(&client->wq_lock);

	guc_wq_item_append(client, 0, 0, 0, 0);
	guc_ring_doorbell(client);

	spin_unlock_irq(&client->wq_lock);

	client->use_nop_wqi = false;

	/* if there are no issues GuC will update the WQ head and keep the
	 * WQ in active status
	 */
	err = wait_for(READ_ONCE(desc->head) == READ_ONCE(desc->tail), 10);
	if (err) {
		pr_err("doorbell %u ring failed!\n", client->doorbell_id);
		return -EIO;
	}

	if (desc->wq_status != WQ_STATUS_ACTIVE) {
		pr_err("doorbell %u ring put WQ in bad state (%u)!\n",
		       client->doorbell_id, desc->wq_status);
		return -EIO;
	}

	return 0;
}