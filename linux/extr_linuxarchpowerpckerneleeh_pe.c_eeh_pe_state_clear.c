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
 int /*<<< orphan*/  __eeh_pe_state_clear ; 
 int /*<<< orphan*/  eeh_pe_traverse (struct eeh_pe*,int /*<<< orphan*/ ,int*) ; 

void eeh_pe_state_clear(struct eeh_pe *pe, int state)
{
	eeh_pe_traverse(pe, __eeh_pe_state_clear, &state);
}