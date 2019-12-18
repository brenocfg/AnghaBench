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

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  IS_ALIGNED (int,int) ; 
 int MI_FLUSH_DW ; 
 int MI_FLUSH_DW_OP_STOREDW ; 
 int MI_FLUSH_DW_USE_GTT ; 

__attribute__((used)) static inline u32 *
gen8_emit_ggtt_write(u32 *cs, u32 value, u32 gtt_offset, u32 flags)
{
	/* w/a: bit 5 needs to be zero for MI_FLUSH_DW address. */
	GEM_BUG_ON(gtt_offset & (1 << 5));
	/* Offset should be aligned to 8 bytes for both (QW/DW) write types */
	GEM_BUG_ON(!IS_ALIGNED(gtt_offset, 8));

	*cs++ = (MI_FLUSH_DW + 1) | MI_FLUSH_DW_OP_STOREDW | flags;
	*cs++ = gtt_offset | MI_FLUSH_DW_USE_GTT;
	*cs++ = 0;
	*cs++ = value;

	return cs;
}