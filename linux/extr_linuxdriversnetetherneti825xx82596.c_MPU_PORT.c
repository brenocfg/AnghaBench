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
struct net_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void MPU_PORT(struct net_device *dev, int c, volatile void *x)
{
#ifdef ENABLE_MVME16x_NET
	if (MACH_IS_MVME16x) {
		struct i596_reg *p = (struct i596_reg *) (dev->base_addr);
		p->porthi = ((c) | (u32) (x)) & 0xffff;
		p->portlo = ((c) | (u32) (x)) >> 16;
	}
#endif
#ifdef ENABLE_BVME6000_NET
	if (MACH_IS_BVME6000) {
		u32 v = (u32) (c) | (u32) (x);
		v = ((u32) (v) << 16) | ((u32) (v) >> 16);
		*(volatile u32 *) dev->base_addr = v;
		udelay(1);
		*(volatile u32 *) dev->base_addr = v;
	}
#endif
}