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
 int /*<<< orphan*/  rodata ; 

void lkdtm_WRITE_RO(void)
{
	/* Explicitly cast away "const" for the test. */
	unsigned long *ptr = (unsigned long *)&rodata;

	pr_info("attempting bad rodata write at %px\n", ptr);
	*ptr ^= 0xabcd1234;
}