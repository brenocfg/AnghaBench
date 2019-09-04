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
struct pt_regs {int ARM_r9; } ;
typedef  int /*<<< orphan*/  dma_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_fiq_regs (struct pt_regs*) ; 

__attribute__((used)) static int floppy_get_residue(unsigned int chan, dma_t *dma)
{
	struct pt_regs regs;
	get_fiq_regs(&regs);
	return regs.ARM_r9;
}