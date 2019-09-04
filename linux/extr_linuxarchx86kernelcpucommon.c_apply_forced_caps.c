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
struct cpuinfo_x86 {int /*<<< orphan*/ * x86_capability; } ;

/* Variables and functions */
 int NBUGINTS ; 
 int NCAPINTS ; 
 int /*<<< orphan*/ * cpu_caps_cleared ; 
 int /*<<< orphan*/ * cpu_caps_set ; 

__attribute__((used)) static void apply_forced_caps(struct cpuinfo_x86 *c)
{
	int i;

	for (i = 0; i < NCAPINTS + NBUGINTS; i++) {
		c->x86_capability[i] &= ~cpu_caps_cleared[i];
		c->x86_capability[i] |= cpu_caps_set[i];
	}
}