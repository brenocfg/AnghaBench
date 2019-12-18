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
typedef  size_t u64 ;
struct vmci_queue {TYPE_3__* kernel_if; } ;
struct ppn_set {int initialized; size_t num_produce_pages; size_t num_consume_pages; size_t* produce_ppns; size_t* consume_ppns; } ;
struct TYPE_4__ {size_t* pas; } ;
struct TYPE_5__ {TYPE_1__ g; } ;
struct TYPE_6__ {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t PAGE_SHIFT ; 
 int VMCI_ERROR_ALREADY_EXISTS ; 
 int VMCI_ERROR_INVALID_ARGS ; 
 int VMCI_ERROR_NO_MEM ; 
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  kfree (size_t*) ; 
 size_t* kmalloc_array (size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qp_alloc_ppn_set(void *prod_q,
			    u64 num_produce_pages,
			    void *cons_q,
			    u64 num_consume_pages, struct ppn_set *ppn_set)
{
	u64 *produce_ppns;
	u64 *consume_ppns;
	struct vmci_queue *produce_q = prod_q;
	struct vmci_queue *consume_q = cons_q;
	u64 i;

	if (!produce_q || !num_produce_pages || !consume_q ||
	    !num_consume_pages || !ppn_set)
		return VMCI_ERROR_INVALID_ARGS;

	if (ppn_set->initialized)
		return VMCI_ERROR_ALREADY_EXISTS;

	produce_ppns =
	    kmalloc_array(num_produce_pages, sizeof(*produce_ppns),
			  GFP_KERNEL);
	if (!produce_ppns)
		return VMCI_ERROR_NO_MEM;

	consume_ppns =
	    kmalloc_array(num_consume_pages, sizeof(*consume_ppns),
			  GFP_KERNEL);
	if (!consume_ppns) {
		kfree(produce_ppns);
		return VMCI_ERROR_NO_MEM;
	}

	for (i = 0; i < num_produce_pages; i++)
		produce_ppns[i] =
			produce_q->kernel_if->u.g.pas[i] >> PAGE_SHIFT;

	for (i = 0; i < num_consume_pages; i++)
		consume_ppns[i] =
			consume_q->kernel_if->u.g.pas[i] >> PAGE_SHIFT;

	ppn_set->num_produce_pages = num_produce_pages;
	ppn_set->num_consume_pages = num_consume_pages;
	ppn_set->produce_ppns = produce_ppns;
	ppn_set->consume_ppns = consume_ppns;
	ppn_set->initialized = true;
	return VMCI_SUCCESS;
}