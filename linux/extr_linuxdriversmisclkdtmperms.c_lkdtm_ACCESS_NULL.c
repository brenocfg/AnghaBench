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
 int /*<<< orphan*/  pr_info (char*,unsigned long*) ; 

void lkdtm_ACCESS_NULL(void)
{
	unsigned long tmp;
	unsigned long *ptr = (unsigned long *)NULL;

	pr_info("attempting bad read at %px\n", ptr);
	tmp = *ptr;
	tmp += 0xc0dec0de;

	pr_info("attempting bad write at %px\n", ptr);
	*ptr = tmp;
}