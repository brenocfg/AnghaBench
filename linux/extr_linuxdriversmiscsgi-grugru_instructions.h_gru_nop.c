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
struct gru_instruction {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CB_IMA (int) ; 
 int /*<<< orphan*/  OP_NOP ; 
 int /*<<< orphan*/  __opdword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gru_start_instruction (struct gru_instruction*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void gru_nop(void *cb, int hints)
{
	struct gru_instruction *ins = (void *)cb;

	gru_start_instruction(ins, __opdword(OP_NOP, 0, 0, 0, 0, 0, CB_IMA(hints)));
}