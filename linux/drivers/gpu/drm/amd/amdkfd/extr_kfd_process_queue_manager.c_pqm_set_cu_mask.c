#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct queue_properties {int /*<<< orphan*/  cu_mask; int /*<<< orphan*/  cu_mask_count; } ;
struct process_queue_node {TYPE_5__* q; } ;
struct process_queue_manager {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  cu_mask; int /*<<< orphan*/  cu_mask_count; } ;
struct TYPE_10__ {TYPE_3__* device; TYPE_1__ properties; } ;
struct TYPE_7__ {int (* update_queue ) (TYPE_4__*,TYPE_5__*) ;} ;
struct TYPE_9__ {TYPE_2__ ops; } ;
struct TYPE_8__ {TYPE_4__* dqm; } ;

/* Variables and functions */
 int EFAULT ; 
 struct process_queue_node* get_queue_by_qid (struct process_queue_manager*,unsigned int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 
 int stub1 (TYPE_4__*,TYPE_5__*) ; 

int pqm_set_cu_mask(struct process_queue_manager *pqm, unsigned int qid,
			struct queue_properties *p)
{
	int retval;
	struct process_queue_node *pqn;

	pqn = get_queue_by_qid(pqm, qid);
	if (!pqn) {
		pr_debug("No queue %d exists for update operation\n", qid);
		return -EFAULT;
	}

	/* Free the old CU mask memory if it is already allocated, then
	 * allocate memory for the new CU mask.
	 */
	kfree(pqn->q->properties.cu_mask);

	pqn->q->properties.cu_mask_count = p->cu_mask_count;
	pqn->q->properties.cu_mask = p->cu_mask;

	retval = pqn->q->device->dqm->ops.update_queue(pqn->q->device->dqm,
							pqn->q);
	if (retval != 0)
		return retval;

	return 0;
}