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
struct process_queue_manager {struct kfd_process* process; int /*<<< orphan*/  queue_slot_bitmap; int /*<<< orphan*/  queues; } ;
struct kfd_process {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_BYTE ; 
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KFD_MAX_NUM_OF_QUEUES_PER_PROCESS ; 
 int /*<<< orphan*/  kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pqm_init(struct process_queue_manager *pqm, struct kfd_process *p)
{
	INIT_LIST_HEAD(&pqm->queues);
	pqm->queue_slot_bitmap =
			kzalloc(DIV_ROUND_UP(KFD_MAX_NUM_OF_QUEUES_PER_PROCESS,
					BITS_PER_BYTE), GFP_KERNEL);
	if (!pqm->queue_slot_bitmap)
		return -ENOMEM;
	pqm->process = p;

	return 0;
}