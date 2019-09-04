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
struct mvpp2_prs_entry {int index; int* tcam; void** sram; } ;
struct mvpp2 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_DATA_REG (int) ; 
 int /*<<< orphan*/  MVPP2_PRS_SRAM_IDX_REG ; 
 int MVPP2_PRS_SRAM_WORDS ; 
 int /*<<< orphan*/  MVPP2_PRS_TCAM_DATA_REG (int) ; 
 int MVPP2_PRS_TCAM_ENTRY_INVALID ; 
 int /*<<< orphan*/  MVPP2_PRS_TCAM_IDX_REG ; 
 int MVPP2_PRS_TCAM_INV_MASK ; 
 size_t MVPP2_PRS_TCAM_INV_WORD ; 
 int MVPP2_PRS_TCAM_SRAM_SIZE ; 
 int MVPP2_PRS_TCAM_WORDS ; 
 int /*<<< orphan*/  memset (struct mvpp2_prs_entry*,int /*<<< orphan*/ ,int) ; 
 void* mvpp2_read (struct mvpp2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_write (struct mvpp2*,int /*<<< orphan*/ ,int) ; 

int mvpp2_prs_init_from_hw(struct mvpp2 *priv, struct mvpp2_prs_entry *pe,
			   int tid)
{
	int i;

	if (tid > MVPP2_PRS_TCAM_SRAM_SIZE - 1)
		return -EINVAL;

	memset(pe, 0, sizeof(*pe));
	pe->index = tid;

	/* Write tcam index - indirect access */
	mvpp2_write(priv, MVPP2_PRS_TCAM_IDX_REG, pe->index);

	pe->tcam[MVPP2_PRS_TCAM_INV_WORD] = mvpp2_read(priv,
			      MVPP2_PRS_TCAM_DATA_REG(MVPP2_PRS_TCAM_INV_WORD));
	if (pe->tcam[MVPP2_PRS_TCAM_INV_WORD] & MVPP2_PRS_TCAM_INV_MASK)
		return MVPP2_PRS_TCAM_ENTRY_INVALID;

	for (i = 0; i < MVPP2_PRS_TCAM_WORDS; i++)
		pe->tcam[i] = mvpp2_read(priv, MVPP2_PRS_TCAM_DATA_REG(i));

	/* Write sram index - indirect access */
	mvpp2_write(priv, MVPP2_PRS_SRAM_IDX_REG, pe->index);
	for (i = 0; i < MVPP2_PRS_SRAM_WORDS; i++)
		pe->sram[i] = mvpp2_read(priv, MVPP2_PRS_SRAM_DATA_REG(i));

	return 0;
}