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
typedef  int u32 ;
struct igc_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_IVAR0 ; 
 int IGC_IVAR_VALID ; 
 int array_rd32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  array_wr32 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void igc_write_ivar(struct igc_hw *hw, int msix_vector,
			   int index, int offset)
{
	u32 ivar = array_rd32(IGC_IVAR0, index);

	/* clear any bits that are currently set */
	ivar &= ~((u32)0xFF << offset);

	/* write vector and valid bit */
	ivar |= (msix_vector | IGC_IVAR_VALID) << offset;

	array_wr32(IGC_IVAR0, index, ivar);
}