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
struct temac_local {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HARD_ACS_RDY_POLL_NS ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  hard_acs_rdy (struct temac_local*) ; 
 int /*<<< orphan*/  hard_acs_rdy_or_timeout (struct temac_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  spin_until_cond (int /*<<< orphan*/ ) ; 

int temac_indirect_busywait(struct temac_local *lp)
{
	ktime_t timeout = ktime_add_ns(ktime_get(), HARD_ACS_RDY_POLL_NS);

	spin_until_cond(hard_acs_rdy_or_timeout(lp, timeout));
	if (WARN_ON(!hard_acs_rdy(lp)))
		return -ETIMEDOUT;
	else
		return 0;
}