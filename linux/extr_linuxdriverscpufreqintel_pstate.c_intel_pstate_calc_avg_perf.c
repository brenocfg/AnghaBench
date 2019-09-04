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
struct sample {int /*<<< orphan*/  mperf; int /*<<< orphan*/  aperf; int /*<<< orphan*/  core_avg_perf; } ;
struct cpudata {struct sample sample; } ;

/* Variables and functions */
 int /*<<< orphan*/  div_ext_fp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void intel_pstate_calc_avg_perf(struct cpudata *cpu)
{
	struct sample *sample = &cpu->sample;

	sample->core_avg_perf = div_ext_fp(sample->aperf, sample->mperf);
}