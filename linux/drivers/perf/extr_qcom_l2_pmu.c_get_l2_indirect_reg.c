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

/* Variables and functions */
 int /*<<< orphan*/  L2CPUSRDR_EL1 ; 
 int /*<<< orphan*/  L2CPUSRSELR_EL1 ; 
 int /*<<< orphan*/  isb () ; 
 int /*<<< orphan*/  l2_access_lock ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_sysreg_s (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_sysreg_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 get_l2_indirect_reg(u64 reg)
{
	u64 val;
	unsigned long flags;

	raw_spin_lock_irqsave(&l2_access_lock, flags);
	write_sysreg_s(reg, L2CPUSRSELR_EL1);
	isb();
	val = read_sysreg_s(L2CPUSRDR_EL1);
	raw_spin_unlock_irqrestore(&l2_access_lock, flags);

	return val;
}