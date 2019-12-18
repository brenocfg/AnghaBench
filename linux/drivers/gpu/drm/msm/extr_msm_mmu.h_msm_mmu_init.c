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
struct msm_mmu_funcs {int dummy; } ;
struct msm_mmu {struct msm_mmu_funcs const* funcs; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void msm_mmu_init(struct msm_mmu *mmu, struct device *dev,
		const struct msm_mmu_funcs *funcs)
{
	mmu->dev = dev;
	mmu->funcs = funcs;
}