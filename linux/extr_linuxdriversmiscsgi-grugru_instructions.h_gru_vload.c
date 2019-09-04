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
struct gru_instruction {long baddr0; unsigned long nelem; unsigned long op1_stride; } ;

/* Variables and functions */
 int /*<<< orphan*/  CB_IMA (unsigned long) ; 
 int /*<<< orphan*/  IAA_RAM ; 
 int /*<<< orphan*/  OP_VLOAD ; 
 int /*<<< orphan*/  __opdword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gru_start_instruction (struct gru_instruction*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void gru_vload(void *cb, unsigned long mem_addr,
		unsigned int tri0, unsigned char xtype, unsigned long nelem,
		unsigned long stride, unsigned long hints)
{
	struct gru_instruction *ins = (struct gru_instruction *)cb;

	ins->baddr0 = (long)mem_addr;
	ins->nelem = nelem;
	ins->op1_stride = stride;
	gru_start_instruction(ins, __opdword(OP_VLOAD, 0, xtype, IAA_RAM, 0,
					(unsigned long)tri0, CB_IMA(hints)));
}