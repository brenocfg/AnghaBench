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
struct adreno_gpu {int /*<<< orphan*/  base; scalar_t__* reg_offsets; } ;
typedef  enum adreno_regs { ____Placeholder_adreno_regs } adreno_regs ;

/* Variables and functions */
 scalar_t__ adreno_reg_check (struct adreno_gpu*,int) ; 
 int /*<<< orphan*/  gpu_write (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void adreno_gpu_write(struct adreno_gpu *gpu,
		enum adreno_regs offset_name, u32 data)
{
	u32 reg = gpu->reg_offsets[offset_name];
	if(adreno_reg_check(gpu, offset_name))
		gpu_write(&gpu->base, reg - 1, data);
}