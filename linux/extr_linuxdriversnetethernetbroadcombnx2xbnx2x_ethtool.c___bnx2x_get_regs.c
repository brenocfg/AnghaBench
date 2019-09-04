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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int DUMP_MAX_PRESETS ; 
 int /*<<< orphan*/  __bnx2x_get_preset_regs (struct bnx2x*,int*,int) ; 
 int /*<<< orphan*/  __bnx2x_get_preset_regs_len (struct bnx2x*,int) ; 

__attribute__((used)) static void __bnx2x_get_regs(struct bnx2x *bp, u32 *p)
{
	u32 preset_idx;

	/* Read all registers, by reading all preset registers */
	for (preset_idx = 1; preset_idx <= DUMP_MAX_PRESETS; preset_idx++) {
		/* Skip presets with IOR */
		if ((preset_idx == 2) ||
		    (preset_idx == 5) ||
		    (preset_idx == 8) ||
		    (preset_idx == 11))
			continue;
		__bnx2x_get_preset_regs(bp, p, preset_idx);
		p += __bnx2x_get_preset_regs_len(bp, preset_idx);
	}
}