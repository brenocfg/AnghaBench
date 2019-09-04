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
struct adreno_gpu {scalar_t__* reg_offsets; } ;
typedef  enum adreno_regs { ____Placeholder_adreno_regs } adreno_regs ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int REG_ADRENO_REGISTER_MAX ; 
 scalar_t__ REG_SKIP ; 

__attribute__((used)) static inline bool adreno_reg_check(struct adreno_gpu *gpu,
		enum adreno_regs offset_name)
{
	if (offset_name >= REG_ADRENO_REGISTER_MAX ||
			!gpu->reg_offsets[offset_name]) {
		BUG();
	}

	/*
	 * REG_SKIP is a special value that tell us that the register in
	 * question isn't implemented on target but don't trigger a BUG(). This
	 * is used to cleanly implement adreno_gpu_write64() and
	 * adreno_gpu_read64() in a generic fashion
	 */
	if (gpu->reg_offsets[offset_name] == REG_SKIP)
		return false;

	return true;
}