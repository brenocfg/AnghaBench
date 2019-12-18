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
typedef  scalar_t__ u64 ;
struct vmci_queue {TYPE_1__* kernel_if; } ;
struct vmci_qp_page_store {scalar_t__ pages; } ;
struct TYPE_2__ {int num_pages; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int qp_host_get_user_memory (scalar_t__,scalar_t__,struct vmci_queue*,struct vmci_queue*) ; 

__attribute__((used)) static int qp_host_register_user_memory(struct vmci_qp_page_store *page_store,
					struct vmci_queue *produce_q,
					struct vmci_queue *consume_q)
{
	u64 produce_uva;
	u64 consume_uva;

	/*
	 * The new style and the old style mapping only differs in
	 * that we either get a single or two UVAs, so we split the
	 * single UVA range at the appropriate spot.
	 */
	produce_uva = page_store->pages;
	consume_uva = page_store->pages +
	    produce_q->kernel_if->num_pages * PAGE_SIZE;
	return qp_host_get_user_memory(produce_uva, consume_uva, produce_q,
				       consume_q);
}