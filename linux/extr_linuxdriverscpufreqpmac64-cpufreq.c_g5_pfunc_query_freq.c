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
typedef  scalar_t__ u32 ;
struct pmf_args {int count; TYPE_1__* u; } ;
struct TYPE_2__ {scalar_t__* p; } ;

/* Variables and functions */
 int CPUFREQ_HIGH ; 
 int CPUFREQ_LOW ; 
 int /*<<< orphan*/  pfunc_cpu_getfreq ; 
 int /*<<< orphan*/  pmf_call_one (int /*<<< orphan*/ ,struct pmf_args*) ; 

__attribute__((used)) static int g5_pfunc_query_freq(void)
{
	struct pmf_args args;
	u32 val = 0;

	args.count = 1;
	args.u[0].p = &val;
	pmf_call_one(pfunc_cpu_getfreq, &args);
	return val ? CPUFREQ_HIGH : CPUFREQ_LOW;
}