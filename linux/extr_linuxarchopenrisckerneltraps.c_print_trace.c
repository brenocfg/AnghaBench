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

/* Variables and functions */
 int /*<<< orphan*/  pr_emerg (char*,void*,char*,void*) ; 

void print_trace(void *data, unsigned long addr, int reliable)
{
	pr_emerg("[<%p>] %s%pS\n", (void *) addr, reliable ? "" : "? ",
	       (void *) addr);
}