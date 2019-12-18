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
struct mvpp2_prs_entry {int* sram; } ;

/* Variables and functions */
 size_t MVPP2_BIT_TO_WORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_OP_SEL_BASE_OFFS ; 
 int MVPP2_PRS_SRAM_OP_SEL_SHIFT_MASK ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_OP_SEL_SHIFT_OFFS ; 
 int MVPP2_PRS_SRAM_SHIFT_MASK ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_SHIFT_OFFS ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_SHIFT_SIGN_BIT ; 
 int /*<<< orphan*/  mvpp2_prs_sram_bits_clear (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_bits_set (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void mvpp2_prs_sram_shift_set(struct mvpp2_prs_entry *pe, int shift,
				     unsigned int op)
{
	/* Set sign */
	if (shift < 0) {
		mvpp2_prs_sram_bits_set(pe, MVPP2_PRS_SRAM_SHIFT_SIGN_BIT, 1);
		shift = 0 - shift;
	} else {
		mvpp2_prs_sram_bits_clear(pe, MVPP2_PRS_SRAM_SHIFT_SIGN_BIT, 1);
	}

	/* Set value */
	pe->sram[MVPP2_BIT_TO_WORD(MVPP2_PRS_SRAM_SHIFT_OFFS)] |=
		shift & MVPP2_PRS_SRAM_SHIFT_MASK;

	/* Reset and set operation */
	mvpp2_prs_sram_bits_clear(pe, MVPP2_PRS_SRAM_OP_SEL_SHIFT_OFFS,
				  MVPP2_PRS_SRAM_OP_SEL_SHIFT_MASK);
	mvpp2_prs_sram_bits_set(pe, MVPP2_PRS_SRAM_OP_SEL_SHIFT_OFFS, op);

	/* Set base offset as current */
	mvpp2_prs_sram_bits_clear(pe, MVPP2_PRS_SRAM_OP_SEL_BASE_OFFS, 1);
}