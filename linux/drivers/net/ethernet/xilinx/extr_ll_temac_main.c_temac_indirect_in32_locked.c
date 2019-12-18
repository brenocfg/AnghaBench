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
struct temac_local {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XTE_CTL0_OFFSET ; 
 int /*<<< orphan*/  XTE_LSW0_OFFSET ; 
 int /*<<< orphan*/  temac_indirect_busywait (struct temac_local*) ; 
 int /*<<< orphan*/  temac_ior (struct temac_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  temac_iow (struct temac_local*,int /*<<< orphan*/ ,int) ; 

u32 temac_indirect_in32_locked(struct temac_local *lp, int reg)
{
	/* This initial wait should normally not spin, as we always
	 * try to wait for indirect access to complete before
	 * releasing the indirect_lock.
	 */
	if (WARN_ON(temac_indirect_busywait(lp)))
		return -ETIMEDOUT;
	/* Initiate read from indirect register */
	temac_iow(lp, XTE_CTL0_OFFSET, reg);
	/* Wait for indirect register access to complete.  We really
	 * should not see timeouts, and could even end up causing
	 * problem for following indirect access, so let's make a bit
	 * of WARN noise.
	 */
	if (WARN_ON(temac_indirect_busywait(lp)))
		return -ETIMEDOUT;
	/* Value is ready now */
	return temac_ior(lp, XTE_LSW0_OFFSET);
}