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
struct process_queue_manager {int /*<<< orphan*/  queue_slot_bitmap; TYPE_1__* process; } ;
struct TYPE_2__ {int /*<<< orphan*/  pasid; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long KFD_MAX_NUM_OF_QUEUES_PER_PROCESS ; 
 unsigned long find_first_zero_bit (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_available_queue_slot(struct process_queue_manager *pqm,
					unsigned int *qid)
{
	unsigned long found;

	found = find_first_zero_bit(pqm->queue_slot_bitmap,
			KFD_MAX_NUM_OF_QUEUES_PER_PROCESS);

	pr_debug("The new slot id %lu\n", found);

	if (found >= KFD_MAX_NUM_OF_QUEUES_PER_PROCESS) {
		pr_info("Cannot open more queues for process with pasid %d\n",
				pqm->process->pasid);
		return -ENOMEM;
	}

	set_bit(found, pqm->queue_slot_bitmap);
	*qid = found;

	return 0;
}