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
struct a6xx_gmu {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ msm_readl (scalar_t__) ; 

__attribute__((used)) static inline u64 gmu_read64(struct a6xx_gmu *gmu, u32 lo, u32 hi)
{
	u64 val;

	val = (u64) msm_readl(gmu->mmio + (lo << 2));
	val |= ((u64) msm_readl(gmu->mmio + (hi << 2)) << 32);

	return val;
}