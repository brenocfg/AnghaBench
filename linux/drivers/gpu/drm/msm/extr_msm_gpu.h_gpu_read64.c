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
typedef  int u64 ;
typedef  int u32 ;
struct msm_gpu {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ msm_readl (scalar_t__) ; 

__attribute__((used)) static inline u64 gpu_read64(struct msm_gpu *gpu, u32 lo, u32 hi)
{
	u64 val;

	/*
	 * Why not a readq here? Two reasons: 1) many of the LO registers are
	 * not quad word aligned and 2) the GPU hardware designers have a bit
	 * of a history of putting registers where they fit, especially in
	 * spins. The longer a GPU family goes the higher the chance that
	 * we'll get burned.  We could do a series of validity checks if we
	 * wanted to, but really is a readq() that much better? Nah.
	 */

	/*
	 * For some lo/hi registers (like perfcounters), the hi value is latched
	 * when the lo is read, so make sure to read the lo first to trigger
	 * that
	 */
	val = (u64) msm_readl(gpu->mmio + (lo << 2));
	val |= ((u64) msm_readl(gpu->mmio + (hi << 2)) << 32);

	return val;
}