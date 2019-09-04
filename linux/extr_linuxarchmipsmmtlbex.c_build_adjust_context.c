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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
#define  CPU_VR4111 135 
#define  CPU_VR4121 134 
#define  CPU_VR4122 133 
#define  CPU_VR4131 132 
#define  CPU_VR4133 131 
#define  CPU_VR4181 130 
#define  CPU_VR4181A 129 
#define  CPU_VR41XX 128 
 int PAGE_SHIFT ; 
 int PTE_T_LOG2 ; 
 int PTRS_PER_PTE ; 
 int /*<<< orphan*/  UASM_i_SRL (int /*<<< orphan*/ **,unsigned int,unsigned int,unsigned int) ; 
 int current_cpu_type () ; 
 int /*<<< orphan*/  uasm_i_andi (int /*<<< orphan*/ **,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void build_adjust_context(u32 **p, unsigned int ctx)
{
	unsigned int shift = 4 - (PTE_T_LOG2 + 1) + PAGE_SHIFT - 12;
	unsigned int mask = (PTRS_PER_PTE / 2 - 1) << (PTE_T_LOG2 + 1);

	switch (current_cpu_type()) {
	case CPU_VR41XX:
	case CPU_VR4111:
	case CPU_VR4121:
	case CPU_VR4122:
	case CPU_VR4131:
	case CPU_VR4181:
	case CPU_VR4181A:
	case CPU_VR4133:
		shift += 2;
		break;

	default:
		break;
	}

	if (shift)
		UASM_i_SRL(p, ctx, ctx, shift);
	uasm_i_andi(p, ctx, ctx, mask);
}