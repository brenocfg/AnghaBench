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
typedef  int /*<<< orphan*/  (* exitcall_t ) () ;

/* Variables and functions */
 int /*<<< orphan*/  __uml_exitcall_begin () ; 
 int /*<<< orphan*/  __uml_exitcall_end () ; 
 int /*<<< orphan*/  stub1 () ; 

void do_uml_exitcalls(void)
{
	exitcall_t *call;

	call = &__uml_exitcall_end;
	while (--call >= &__uml_exitcall_begin)
		(*call)();
}