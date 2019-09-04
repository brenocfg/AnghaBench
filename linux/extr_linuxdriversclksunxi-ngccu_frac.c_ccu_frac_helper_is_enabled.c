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
struct ccu_frac_internal {int enable; } ;
struct ccu_common {int features; scalar_t__ reg; scalar_t__ base; } ;

/* Variables and functions */
 int CCU_FEATURE_FRACTIONAL ; 
 int readl (scalar_t__) ; 

bool ccu_frac_helper_is_enabled(struct ccu_common *common,
				struct ccu_frac_internal *cf)
{
	if (!(common->features & CCU_FEATURE_FRACTIONAL))
		return false;

	return !(readl(common->base + common->reg) & cf->enable);
}