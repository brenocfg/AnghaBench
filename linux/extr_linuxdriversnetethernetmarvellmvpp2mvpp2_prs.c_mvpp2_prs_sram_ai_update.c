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
struct mvpp2_prs_entry {int dummy; } ;

/* Variables and functions */
 unsigned int BIT (unsigned int) ; 
 unsigned int MVPP2_PRS_SRAM_AI_CTRL_BITS ; 
 scalar_t__ MVPP2_PRS_SRAM_AI_CTRL_OFFS ; 
 scalar_t__ MVPP2_PRS_SRAM_AI_OFFS ; 
 int /*<<< orphan*/  mvpp2_prs_sram_bits_clear (struct mvpp2_prs_entry*,scalar_t__,int) ; 
 int /*<<< orphan*/  mvpp2_prs_sram_bits_set (struct mvpp2_prs_entry*,scalar_t__,int) ; 

__attribute__((used)) static void mvpp2_prs_sram_ai_update(struct mvpp2_prs_entry *pe,
				     unsigned int bits, unsigned int mask)
{
	unsigned int i;

	for (i = 0; i < MVPP2_PRS_SRAM_AI_CTRL_BITS; i++) {
		if (!(mask & BIT(i)))
			continue;

		if (bits & BIT(i))
			mvpp2_prs_sram_bits_set(pe, MVPP2_PRS_SRAM_AI_OFFS + i,
						1);
		else
			mvpp2_prs_sram_bits_clear(pe,
						  MVPP2_PRS_SRAM_AI_OFFS + i,
						  1);

		mvpp2_prs_sram_bits_set(pe, MVPP2_PRS_SRAM_AI_CTRL_OFFS + i, 1);
	}
}