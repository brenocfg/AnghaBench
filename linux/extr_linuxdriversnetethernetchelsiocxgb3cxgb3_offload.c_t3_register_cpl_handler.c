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
typedef  scalar_t__ cpl_handler_func ;

/* Variables and functions */
 unsigned int NUM_CPL_CMDS ; 
 scalar_t__* cpl_handlers ; 
 scalar_t__ do_bad_cpl ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 

void t3_register_cpl_handler(unsigned int opcode, cpl_handler_func h)
{
	if (opcode < NUM_CPL_CMDS)
		cpl_handlers[opcode] = h ? h : do_bad_cpl;
	else
		pr_err("T3C: handler registration for opcode %x failed\n",
		       opcode);
}