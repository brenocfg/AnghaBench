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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,scalar_t__) ; 
 scalar_t__ INSTR_BC_CLIENT ; 
 scalar_t__ INSTR_CLIENT_SHIFT ; 
 scalar_t__ INSTR_MI_CLIENT ; 

__attribute__((used)) static u32 gen9_blt_get_cmd_length_mask(u32 cmd_header)
{
	u32 client = cmd_header >> INSTR_CLIENT_SHIFT;

	if (client == INSTR_MI_CLIENT || client == INSTR_BC_CLIENT)
		return 0xFF;

	DRM_DEBUG_DRIVER("CMD: Abnormal blt cmd length! 0x%08X\n", cmd_header);
	return 0;
}