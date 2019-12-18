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
struct omap_sr {scalar_t__ ip_type; unsigned int base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCONFIG_STATUS_V1_MASK ; 
 unsigned int ERRCONFIG_V1 ; 
 unsigned int ERRCONFIG_V2 ; 
 int /*<<< orphan*/  ERRCONFIG_VPBOUNDINTST_V2 ; 
 scalar_t__ SR_TYPE_V1 ; 
 scalar_t__ SR_TYPE_V2 ; 
 int /*<<< orphan*/  __raw_readl (unsigned int) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void sr_modify_reg(struct omap_sr *sr, unsigned offset, u32 mask,
					u32 value)
{
	u32 reg_val;

	/*
	 * Smartreflex error config register is special as it contains
	 * certain status bits which if written a 1 into means a clear
	 * of those bits. So in order to make sure no accidental write of
	 * 1 happens to those status bits, do a clear of them in the read
	 * value. This mean this API doesn't rewrite values in these bits
	 * if they are currently set, but does allow the caller to write
	 * those bits.
	 */
	if (sr->ip_type == SR_TYPE_V1 && offset == ERRCONFIG_V1)
		mask |= ERRCONFIG_STATUS_V1_MASK;
	else if (sr->ip_type == SR_TYPE_V2 && offset == ERRCONFIG_V2)
		mask |= ERRCONFIG_VPBOUNDINTST_V2;

	reg_val = __raw_readl(sr->base + offset);
	reg_val &= ~mask;

	value &= mask;

	reg_val |= value;

	__raw_writel(reg_val, (sr->base + offset));
}