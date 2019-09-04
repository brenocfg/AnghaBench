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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int (* get_alternatives ) (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int MAX_EVENT_ALTERNATIVES ; 
 unsigned long PPMU_LIMITED_PMC_OK ; 
 unsigned long PPMU_LIMITED_PMC_REQD ; 
 TYPE_1__* ppmu ; 
 int stub1 (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 normal_pmc_alternative(u64 ev, unsigned long flags)
{
	u64 alt[MAX_EVENT_ALTERNATIVES];
	int n;

	flags &= ~(PPMU_LIMITED_PMC_OK | PPMU_LIMITED_PMC_REQD);
	n = ppmu->get_alternatives(ev, flags, alt);
	if (!n)
		return 0;
	return alt[0];
}