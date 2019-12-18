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
 int /*<<< orphan*/  pr_warn (char*,char const* const,char const* const) ; 
 int /*<<< orphan*/  tpacpi_log_usertask (char*) ; 

__attribute__((used)) static void printk_deprecated_attribute(const char * const what,
					const char * const details)
{
	tpacpi_log_usertask("deprecated sysfs attribute");
	pr_warn("WARNING: sysfs attribute %s is deprecated and will be removed. %s\n",
		what, details);
}