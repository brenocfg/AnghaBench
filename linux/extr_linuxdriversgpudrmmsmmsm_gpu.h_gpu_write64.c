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
typedef  int u32 ;
struct msm_gpu {scalar_t__ mmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void gpu_write64(struct msm_gpu *gpu, u32 lo, u32 hi, u64 val)
{
	/* Why not a writeq here? Read the screed above */
	msm_writel(lower_32_bits(val), gpu->mmio + (lo << 2));
	msm_writel(upper_32_bits(val), gpu->mmio + (hi << 2));
}