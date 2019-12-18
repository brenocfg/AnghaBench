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
typedef  int /*<<< orphan*/  u64 ;
struct adreno_gpu {int dummy; } ;
typedef  enum adreno_regs { ____Placeholder_adreno_regs } adreno_regs ;

/* Variables and functions */
 int /*<<< orphan*/  adreno_gpu_write (struct adreno_gpu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void adreno_gpu_write64(struct adreno_gpu *gpu,
		enum adreno_regs lo, enum adreno_regs hi, u64 data)
{
	adreno_gpu_write(gpu, lo, lower_32_bits(data));
	adreno_gpu_write(gpu, hi, upper_32_bits(data));
}