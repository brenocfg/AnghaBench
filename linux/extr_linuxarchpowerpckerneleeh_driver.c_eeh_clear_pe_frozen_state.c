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
struct eeh_pe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEH_PE_ISOLATED ; 
 int EIO ; 
 int /*<<< orphan*/  __eeh_clear_pe_frozen_state ; 
 int /*<<< orphan*/  eeh_pe_state_clear (struct eeh_pe*,int /*<<< orphan*/ ) ; 
 void* eeh_pe_traverse (struct eeh_pe*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int eeh_clear_pe_frozen_state(struct eeh_pe *pe,
				     bool clear_sw_state)
{
	void *rc;

	rc = eeh_pe_traverse(pe, __eeh_clear_pe_frozen_state, &clear_sw_state);
	if (!rc)
		eeh_pe_state_clear(pe, EEH_PE_ISOLATED);

	return rc ? -EIO : 0;
}