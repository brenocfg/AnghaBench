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
 int /*<<< orphan*/  pr_warn (char*,char const*,char const*) ; 

__attribute__((used)) static inline int validate_dt_prop_sizes(const char *prop1, int prop1_len,
					 const char *prop2, int prop2_len)
{
	if (prop1_len == prop2_len)
		return 0;

	pr_warn("cpuidle-powernv: array sizes don't match for %s and %s\n",
		prop1, prop2);
	return -1;
}