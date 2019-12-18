#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct vmci_queue_header {int dummy; } ;
struct vmci_queue {struct vmci_queue_header* q_header; TYPE_3__* kernel_if; } ;
struct page {int dummy; } ;
struct TYPE_4__ {struct page** header_page; } ;
struct TYPE_5__ {TYPE_1__ h; } ;
struct TYPE_6__ {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int PAGE_SIZE ; 
 int VMCI_ERROR_NO_MEM ; 
 int VMCI_ERROR_QUEUEPAIR_MISMATCH ; 
 int VMCI_ERROR_UNAVAILABLE ; 
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  VM_MAP ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 struct vmci_queue_header* vmap (struct page**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qp_host_map_queues(struct vmci_queue *produce_q,
			      struct vmci_queue *consume_q)
{
	int result;

	if (!produce_q->q_header || !consume_q->q_header) {
		struct page *headers[2];

		if (produce_q->q_header != consume_q->q_header)
			return VMCI_ERROR_QUEUEPAIR_MISMATCH;

		if (produce_q->kernel_if->u.h.header_page == NULL ||
		    *produce_q->kernel_if->u.h.header_page == NULL)
			return VMCI_ERROR_UNAVAILABLE;

		headers[0] = *produce_q->kernel_if->u.h.header_page;
		headers[1] = *consume_q->kernel_if->u.h.header_page;

		produce_q->q_header = vmap(headers, 2, VM_MAP, PAGE_KERNEL);
		if (produce_q->q_header != NULL) {
			consume_q->q_header =
			    (struct vmci_queue_header *)((u8 *)
							 produce_q->q_header +
							 PAGE_SIZE);
			result = VMCI_SUCCESS;
		} else {
			pr_warn("vmap failed\n");
			result = VMCI_ERROR_NO_MEM;
		}
	} else {
		result = VMCI_SUCCESS;
	}

	return result;
}