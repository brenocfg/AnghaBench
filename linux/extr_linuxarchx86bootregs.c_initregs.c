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
struct biosregs {int /*<<< orphan*/  gs; int /*<<< orphan*/  fs; void* es; void* ds; int /*<<< orphan*/  eflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_EFLAGS_CF ; 
 void* ds () ; 
 int /*<<< orphan*/  fs () ; 
 int /*<<< orphan*/  gs () ; 
 int /*<<< orphan*/  memset (struct biosregs*,int /*<<< orphan*/ ,int) ; 

void initregs(struct biosregs *reg)
{
	memset(reg, 0, sizeof *reg);
	reg->eflags |= X86_EFLAGS_CF;
	reg->ds = ds();
	reg->es = ds();
	reg->fs = fs();
	reg->gs = gs();
}