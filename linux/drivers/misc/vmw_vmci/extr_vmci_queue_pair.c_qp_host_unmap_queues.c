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
typedef  int /*<<< orphan*/  u32 ;
struct vmci_queue {int /*<<< orphan*/ * q_header; } ;

/* Variables and functions */
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  vunmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qp_host_unmap_queues(u32 gid,
				struct vmci_queue *produce_q,
				struct vmci_queue *consume_q)
{
	if (produce_q->q_header) {
		if (produce_q->q_header < consume_q->q_header)
			vunmap(produce_q->q_header);
		else
			vunmap(consume_q->q_header);

		produce_q->q_header = NULL;
		consume_q->q_header = NULL;
	}

	return VMCI_SUCCESS;
}