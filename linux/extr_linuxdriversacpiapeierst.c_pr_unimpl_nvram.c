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
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ printk_ratelimit () ; 

__attribute__((used)) static void pr_unimpl_nvram(void)
{
	if (printk_ratelimit())
		pr_warn("NVRAM ERST Log Address Range not implemented yet.\n");
}