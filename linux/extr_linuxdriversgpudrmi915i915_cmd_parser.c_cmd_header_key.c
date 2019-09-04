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
#define  INSTR_BC_CLIENT 130 
 int INSTR_CLIENT_SHIFT ; 
#define  INSTR_MI_CLIENT 129 
#define  INSTR_RC_CLIENT 128 
 int STD_2D_OPCODE_SHIFT ; 
 int STD_3D_OPCODE_SHIFT ; 
 int STD_MI_OPCODE_SHIFT ; 

__attribute__((used)) static inline u32 cmd_header_key(u32 x)
{
	switch (x >> INSTR_CLIENT_SHIFT) {
	default:
	case INSTR_MI_CLIENT:
		return x >> STD_MI_OPCODE_SHIFT;
	case INSTR_RC_CLIENT:
		return x >> STD_3D_OPCODE_SHIFT;
	case INSTR_BC_CLIENT:
		return x >> STD_2D_OPCODE_SHIFT;
	}
}