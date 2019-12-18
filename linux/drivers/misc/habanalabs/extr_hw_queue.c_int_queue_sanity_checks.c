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
struct hl_hw_queue {int /*<<< orphan*/  hw_queue_id; int /*<<< orphan*/  int_queue_len; } ;
struct hl_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int queue_free_slots (struct hl_hw_queue*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int int_queue_sanity_checks(struct hl_device *hdev,
					struct hl_hw_queue *q,
					int num_of_entries)
{
	int free_slots_cnt;

	/* Check we have enough space in the queue */
	free_slots_cnt = queue_free_slots(q, q->int_queue_len);

	if (free_slots_cnt < num_of_entries) {
		dev_dbg(hdev->dev, "Queue %d doesn't have room for %d CBs\n",
			q->hw_queue_id, num_of_entries);
		return -EAGAIN;
	}

	return 0;
}