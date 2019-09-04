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
typedef  scalar_t__ u64 ;
struct pt_regs {unsigned long* gpr; unsigned long nip; unsigned long msr; unsigned long ctr; unsigned long link; unsigned long xer; unsigned long ccr; unsigned long dar; unsigned long dsisr; } ;

/* Variables and functions */
 scalar_t__ REG_ID (char*) ; 
 int fadump_gpr_index (scalar_t__) ; 

__attribute__((used)) static inline void fadump_set_regval(struct pt_regs *regs, u64 reg_id,
								u64 reg_val)
{
	int i;

	i = fadump_gpr_index(reg_id);
	if (i >= 0)
		regs->gpr[i] = (unsigned long)reg_val;
	else if (reg_id == REG_ID("NIA"))
		regs->nip = (unsigned long)reg_val;
	else if (reg_id == REG_ID("MSR"))
		regs->msr = (unsigned long)reg_val;
	else if (reg_id == REG_ID("CTR"))
		regs->ctr = (unsigned long)reg_val;
	else if (reg_id == REG_ID("LR"))
		regs->link = (unsigned long)reg_val;
	else if (reg_id == REG_ID("XER"))
		regs->xer = (unsigned long)reg_val;
	else if (reg_id == REG_ID("CR"))
		regs->ccr = (unsigned long)reg_val;
	else if (reg_id == REG_ID("DAR"))
		regs->dar = (unsigned long)reg_val;
	else if (reg_id == REG_ID("DSISR"))
		regs->dsisr = (unsigned long)reg_val;
}