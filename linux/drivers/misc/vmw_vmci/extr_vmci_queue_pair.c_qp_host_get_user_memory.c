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
typedef  scalar_t__ u64 ;
struct vmci_queue {TYPE_3__* kernel_if; } ;
struct TYPE_4__ {int /*<<< orphan*/  header_page; } ;
struct TYPE_5__ {TYPE_1__ h; } ;
struct TYPE_6__ {int num_pages; TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  FOLL_WRITE ; 
 int VMCI_ERROR_NO_MEM ; 
 int VMCI_SUCCESS ; 
 int get_user_pages_fast (uintptr_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  qp_release_pages (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int qp_host_get_user_memory(u64 produce_uva,
				   u64 consume_uva,
				   struct vmci_queue *produce_q,
				   struct vmci_queue *consume_q)
{
	int retval;
	int err = VMCI_SUCCESS;

	retval = get_user_pages_fast((uintptr_t) produce_uva,
				     produce_q->kernel_if->num_pages,
				     FOLL_WRITE,
				     produce_q->kernel_if->u.h.header_page);
	if (retval < (int)produce_q->kernel_if->num_pages) {
		pr_debug("get_user_pages_fast(produce) failed (retval=%d)",
			retval);
		qp_release_pages(produce_q->kernel_if->u.h.header_page,
				 retval, false);
		err = VMCI_ERROR_NO_MEM;
		goto out;
	}

	retval = get_user_pages_fast((uintptr_t) consume_uva,
				     consume_q->kernel_if->num_pages,
				     FOLL_WRITE,
				     consume_q->kernel_if->u.h.header_page);
	if (retval < (int)consume_q->kernel_if->num_pages) {
		pr_debug("get_user_pages_fast(consume) failed (retval=%d)",
			retval);
		qp_release_pages(consume_q->kernel_if->u.h.header_page,
				 retval, false);
		qp_release_pages(produce_q->kernel_if->u.h.header_page,
				 produce_q->kernel_if->num_pages, false);
		err = VMCI_ERROR_NO_MEM;
	}

 out:
	return err;
}