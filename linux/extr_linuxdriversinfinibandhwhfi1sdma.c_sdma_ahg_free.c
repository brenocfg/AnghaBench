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
struct sdma_engine {int /*<<< orphan*/  ahg_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_hfi1_ahg_deallocate (struct sdma_engine*,int) ; 

void sdma_ahg_free(struct sdma_engine *sde, int ahg_index)
{
	if (!sde)
		return;
	trace_hfi1_ahg_deallocate(sde, ahg_index);
	if (ahg_index < 0 || ahg_index > 31)
		return;
	clear_bit(ahg_index, &sde->ahg_bits);
}