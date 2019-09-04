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

/* Variables and functions */
 int /*<<< orphan*/  PMGC0_FAC ; 
 int /*<<< orphan*/  PMGC0_FCECE ; 
 int /*<<< orphan*/  PMGC0_PMIE ; 
 int /*<<< orphan*/  PMRN_PMGC0 ; 
 int /*<<< orphan*/  mfpmr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtpmr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pmc_start_ctrs(int enable)
{
	u32 pmgc0 = mfpmr(PMRN_PMGC0);

	pmgc0 &= ~PMGC0_FAC;
	pmgc0 |= PMGC0_FCECE;

	if (enable)
		pmgc0 |= PMGC0_PMIE;
	else
		pmgc0 &= ~PMGC0_PMIE;

	mtpmr(PMRN_PMGC0, pmgc0);
}