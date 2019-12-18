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
struct a6xx_gmu {scalar_t__ mmio; } ;

/* Variables and functions */
 void msm_writel (int,scalar_t__) ; 

__attribute__((used)) static inline void gmu_write(struct a6xx_gmu *gmu, u32 offset, u32 value)
{
	return msm_writel(value, gmu->mmio + (offset << 2));
}