#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_2__ {int offset; char* name; } ;

/* Variables and functions */
 int DBG_MAX_REG_NUM ; 
 TYPE_1__* dbg_reg_def ; 

char *dbg_get_reg(int regno, void *mem, struct pt_regs *regs)
{
	if (regno >= DBG_MAX_REG_NUM || regno < 0)
		return NULL;

	*((unsigned long *) mem) = *((unsigned long *) ((void *)regs +
		dbg_reg_def[regno].offset));

	return dbg_reg_def[regno].name;
}