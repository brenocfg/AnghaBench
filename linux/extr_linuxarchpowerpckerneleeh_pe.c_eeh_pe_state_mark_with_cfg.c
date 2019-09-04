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
 int EEH_PE_CFG_BLOCKED ; 
 int EEH_PE_ISOLATED ; 
 int /*<<< orphan*/  __eeh_pe_state_clear ; 
 int /*<<< orphan*/  __eeh_pe_state_mark ; 
 int /*<<< orphan*/  eeh_pe_traverse (struct eeh_pe*,int /*<<< orphan*/ ,int*) ; 

void eeh_pe_state_mark_with_cfg(struct eeh_pe *pe, int state)
{
	eeh_pe_traverse(pe, __eeh_pe_state_mark, &state);
	if (!(state & EEH_PE_ISOLATED))
		return;

	/* Clear EEH_PE_CFG_BLOCKED, which might be set just now */
	state = EEH_PE_CFG_BLOCKED;
	eeh_pe_traverse(pe, __eeh_pe_state_clear, &state);
}