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

/* Variables and functions */
 scalar_t__ __this_cpu_has_cap (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  arm64_errata ; 
 int /*<<< orphan*/  arm64_features ; 

bool this_cpu_has_cap(unsigned int cap)
{
	return (__this_cpu_has_cap(arm64_features, cap) ||
		__this_cpu_has_cap(arm64_errata, cap));
}