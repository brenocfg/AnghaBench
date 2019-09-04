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
struct pt_regs {unsigned long* gprs; } ;

/* Variables and functions */
 unsigned int NUM_GPRS ; 

unsigned long regs_get_register(struct pt_regs *regs, unsigned int offset)
{
	if (offset >= NUM_GPRS)
		return 0;
	return regs->gprs[offset];
}