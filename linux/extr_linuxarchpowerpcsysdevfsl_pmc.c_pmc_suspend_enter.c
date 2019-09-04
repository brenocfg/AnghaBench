#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  suspend_state_t ;
struct TYPE_2__ {int /*<<< orphan*/  pmcsr; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int PMCSR_SLP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int in_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmc_dev ; 
 TYPE_1__* pmc_regs ; 
 int /*<<< orphan*/  setbits32 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ spin_event_timeout (int,int,int) ; 

__attribute__((used)) static int pmc_suspend_enter(suspend_state_t state)
{
	int ret;

	setbits32(&pmc_regs->pmcsr, PMCSR_SLP);
	/* At this point, the CPU is asleep. */

	/* Upon resume, wait for SLP bit to be clear. */
	ret = spin_event_timeout((in_be32(&pmc_regs->pmcsr) & PMCSR_SLP) == 0,
				 10000, 10) ? 0 : -ETIMEDOUT;
	if (ret)
		dev_err(pmc_dev, "tired waiting for SLP bit to clear\n");
	return ret;
}