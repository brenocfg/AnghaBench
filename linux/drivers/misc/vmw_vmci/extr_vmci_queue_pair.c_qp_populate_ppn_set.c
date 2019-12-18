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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct ppn_set {int num_produce_pages; int num_consume_pages; scalar_t__* consume_ppns; scalar_t__* produce_ppns; } ;

/* Variables and functions */
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 scalar_t__ vmci_use_ppn64 () ; 

__attribute__((used)) static int qp_populate_ppn_set(u8 *call_buf, const struct ppn_set *ppn_set)
{
	if (vmci_use_ppn64()) {
		memcpy(call_buf, ppn_set->produce_ppns,
		       ppn_set->num_produce_pages *
		       sizeof(*ppn_set->produce_ppns));
		memcpy(call_buf +
		       ppn_set->num_produce_pages *
		       sizeof(*ppn_set->produce_ppns),
		       ppn_set->consume_ppns,
		       ppn_set->num_consume_pages *
		       sizeof(*ppn_set->consume_ppns));
	} else {
		int i;
		u32 *ppns = (u32 *) call_buf;

		for (i = 0; i < ppn_set->num_produce_pages; i++)
			ppns[i] = (u32) ppn_set->produce_ppns[i];

		ppns = &ppns[ppn_set->num_produce_pages];

		for (i = 0; i < ppn_set->num_consume_pages; i++)
			ppns[i] = (u32) ppn_set->consume_ppns[i];
	}

	return VMCI_SUCCESS;
}