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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;

/* Variables and functions */
 int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_IMMED_A_SRC ; 
 int /*<<< orphan*/  OP_IMMED_B_SRC ; 
 int /*<<< orphan*/  OP_IMMED_IMM ; 
 int /*<<< orphan*/  immed_can_modify (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unreg_is_imm (int) ; 

u16 immed_get_value(u64 instr)
{
	u16 reg;

	if (!immed_can_modify(instr))
		return 0;

	reg = FIELD_GET(OP_IMMED_A_SRC, instr);
	if (!unreg_is_imm(reg))
		reg = FIELD_GET(OP_IMMED_B_SRC, instr);

	return (reg & 0xff) | FIELD_GET(OP_IMMED_IMM, instr) << 8;
}