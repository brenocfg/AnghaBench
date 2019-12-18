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
struct ixp46x_ts_regs {int /*<<< orphan*/  systime_hi; int /*<<< orphan*/  systime_lo; } ;

/* Variables and functions */
 int TICKS_NS_SHIFT ; 
 int __raw_readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 ixp_systime_read(struct ixp46x_ts_regs *regs)
{
	u64 ns;
	u32 lo, hi;

	lo = __raw_readl(&regs->systime_lo);
	hi = __raw_readl(&regs->systime_hi);

	ns = ((u64) hi) << 32;
	ns |= lo;
	ns <<= TICKS_NS_SHIFT;

	return ns;
}