#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cpuinfo_x86 {int x86; scalar_t__ x86_model; scalar_t__ x86_stepping; scalar_t__ microcode; } ;
struct TYPE_3__ {scalar_t__ model; scalar_t__ stepping; scalar_t__ microcode; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  X86_FEATURE_HYPERVISOR ; 
 scalar_t__ cpu_has (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 TYPE_1__* spectre_bad_microcodes ; 

__attribute__((used)) static bool bad_spectre_microcode(struct cpuinfo_x86 *c)
{
	int i;

	/*
	 * We know that the hypervisor lie to us on the microcode version so
	 * we may as well hope that it is running the correct version.
	 */
	if (cpu_has(c, X86_FEATURE_HYPERVISOR))
		return false;

	if (c->x86 != 6)
		return false;

	for (i = 0; i < ARRAY_SIZE(spectre_bad_microcodes); i++) {
		if (c->x86_model == spectre_bad_microcodes[i].model &&
		    c->x86_stepping == spectre_bad_microcodes[i].stepping)
			return (c->microcode <= spectre_bad_microcodes[i].microcode);
	}
	return false;
}