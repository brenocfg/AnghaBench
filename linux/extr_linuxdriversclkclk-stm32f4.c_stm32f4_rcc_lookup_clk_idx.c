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
typedef  int u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  table ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 int BITS_PER_LONG_LONG ; 
 int BIT_ULL_MASK (int) ; 
 int BIT_ULL_WORD (int) ; 
 int EINVAL ; 
 int GENMASK_ULL (int,int /*<<< orphan*/ ) ; 
 int MAX_GATE_MAP ; 
 scalar_t__ WARN_ON (int) ; 
 int hweight64 (int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stm32f4_gate_map ; 
 int stm32fx_end_primary_clk ; 

__attribute__((used)) static int stm32f4_rcc_lookup_clk_idx(u8 primary, u8 secondary)
{
	u64 table[MAX_GATE_MAP];

	if (primary == 1) {
		if (WARN_ON(secondary >= stm32fx_end_primary_clk))
			return -EINVAL;
		return secondary;
	}

	memcpy(table, stm32f4_gate_map, sizeof(table));

	/* only bits set in table can be used as indices */
	if (WARN_ON(secondary >= BITS_PER_BYTE * sizeof(table) ||
		    0 == (table[BIT_ULL_WORD(secondary)] &
			  BIT_ULL_MASK(secondary))))
		return -EINVAL;

	/* mask out bits above our current index */
	table[BIT_ULL_WORD(secondary)] &=
	    GENMASK_ULL(secondary % BITS_PER_LONG_LONG, 0);

	return stm32fx_end_primary_clk - 1 + hweight64(table[0]) +
	       (BIT_ULL_WORD(secondary) >= 1 ? hweight64(table[1]) : 0) +
	       (BIT_ULL_WORD(secondary) >= 2 ? hweight64(table[2]) : 0);
}