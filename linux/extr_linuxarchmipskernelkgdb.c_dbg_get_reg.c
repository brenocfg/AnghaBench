#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int cp0_status; } ;
struct TYPE_9__ {int offset; char* name; int /*<<< orphan*/  size; } ;
struct TYPE_6__ {int /*<<< orphan*/ * fpr; int /*<<< orphan*/  fcr31; } ;
struct TYPE_7__ {TYPE_1__ fpu; } ;
struct TYPE_8__ {TYPE_2__ thread; } ;

/* Variables and functions */
 int DBG_MAX_REG_NUM ; 
 int ST0_CU1 ; 
 TYPE_3__* current ; 
 TYPE_4__* dbg_reg_def ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_fp (TYPE_3__*) ; 

char *dbg_get_reg(int regno, void *mem, struct pt_regs *regs)
{
	int fp_reg;

	if (regno >= DBG_MAX_REG_NUM || regno < 0)
		return NULL;

	if (dbg_reg_def[regno].offset != -1 && regno < 38) {
		/* First 38 registers */
		memcpy(mem, (void *)regs + dbg_reg_def[regno].offset,
		       dbg_reg_def[regno].size);
	} else if (current && dbg_reg_def[regno].offset != -1 && regno < 72) {
		/* FP registers 38 -> 69 */
		if (!(regs->cp0_status & ST0_CU1))
			goto out;
		save_fp(current);
		if (regno == 70) {
			/* Process the fcr31/fsr (register 70) */
			memcpy(mem, (void *)&current->thread.fpu.fcr31,
			       dbg_reg_def[regno].size);
			goto out;
		} else if (regno == 71) {
			/* Ignore the fir (register 71) */
			memset(mem, 0, dbg_reg_def[regno].size);
			goto out;
		}
		fp_reg = dbg_reg_def[regno].offset;
		memcpy(mem, (void *)&current->thread.fpu.fpr[fp_reg],
		       dbg_reg_def[regno].size);
	}

out:
	return dbg_reg_def[regno].name;

}