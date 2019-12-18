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
 int called_count ; 
 scalar_t__ lkdtm_increment_int ; 
 void lkdtm_increment_void (int*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

void lkdtm_CFI_FORWARD_PROTO(void)
{
	/*
	 * Matches lkdtm_increment_void()'s prototype, but not
	 * lkdtm_increment_int()'s prototype.
	 */
	void (*func)(int *);

	pr_info("Calling matched prototype ...\n");
	func = lkdtm_increment_void;
	func(&called_count);

	pr_info("Calling mismatched prototype ...\n");
	func = (void *)lkdtm_increment_int;
	func(&called_count);

	pr_info("Fail: survived mismatched prototype function call!\n");
}