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
struct pmu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable_all ) () ;} ;

/* Variables and functions */
 TYPE_1__* sh_pmu ; 
 int /*<<< orphan*/  sh_pmu_initialized () ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void sh_pmu_enable(struct pmu *pmu)
{
	if (!sh_pmu_initialized())
		return;

	sh_pmu->enable_all();
}