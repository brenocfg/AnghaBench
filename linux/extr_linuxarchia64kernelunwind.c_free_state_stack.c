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
struct unw_reg_state {struct unw_reg_state* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_reg_state (struct unw_reg_state*) ; 

__attribute__((used)) static void
free_state_stack (struct unw_reg_state *rs)
{
	struct unw_reg_state *p, *next;

	for (p = rs->next; p != NULL; p = next) {
		next = p->next;
		free_reg_state(p);
	}
	rs->next = NULL;
}