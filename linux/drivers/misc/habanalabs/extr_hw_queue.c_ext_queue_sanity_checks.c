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
struct hl_hw_queue {size_t hw_queue_id; } ;
struct hl_device {int /*<<< orphan*/  dev; TYPE_1__* completion_queue; } ;
typedef  int /*<<< orphan*/  atomic_t ;
struct TYPE_2__ {int /*<<< orphan*/  free_slots_cnt; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  HL_QUEUE_LENGTH ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_add_negative (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int queue_free_slots (struct hl_hw_queue*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext_queue_sanity_checks(struct hl_device *hdev,
				struct hl_hw_queue *q, int num_of_entries,
				bool reserve_cq_entry)
{
	atomic_t *free_slots =
			&hdev->completion_queue[q->hw_queue_id].free_slots_cnt;
	int free_slots_cnt;

	/* Check we have enough space in the queue */
	free_slots_cnt = queue_free_slots(q, HL_QUEUE_LENGTH);

	if (free_slots_cnt < num_of_entries) {
		dev_dbg(hdev->dev, "Queue %d doesn't have room for %d CBs\n",
			q->hw_queue_id, num_of_entries);
		return -EAGAIN;
	}

	if (reserve_cq_entry) {
		/*
		 * Check we have enough space in the completion queue
		 * Add -1 to counter (decrement) unless counter was already 0
		 * In that case, CQ is full so we can't submit a new CB because
		 * we won't get ack on its completion
		 * atomic_add_unless will return 0 if counter was already 0
		 */
		if (atomic_add_negative(num_of_entries * -1, free_slots)) {
			dev_dbg(hdev->dev, "No space for %d on CQ %d\n",
				num_of_entries, q->hw_queue_id);
			atomic_add(num_of_entries, free_slots);
			return -EAGAIN;
		}
	}

	return 0;
}