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
struct pt_regs {scalar_t__ ip; } ;

/* Variables and functions */
 scalar_t__ kgdb_isremovedbreak (scalar_t__) ; 

int kgdb_skipexception(int exception, struct pt_regs *regs)
{
	if (exception == 3 && kgdb_isremovedbreak(regs->ip - 1)) {
		regs->ip -= 1;
		return 1;
	}
	return 0;
}