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
typedef  int /*<<< orphan*/  refcount_t ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  REFCOUNT_INIT (int) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

void lkdtm_REFCOUNT_TIMING(void)
{
	unsigned int i;
	refcount_t count = REFCOUNT_INIT(1);

	for (i = 0; i < INT_MAX - 1; i++)
		refcount_inc(&count);

	for (i = INT_MAX; i > 0; i--)
		if (refcount_dec_and_test(&count))
			break;

	if (i != 1)
		pr_err("refcount: out of sync up/down cycle: %u\n", i - 1);
	else
		pr_info("refcount timing: done\n");
}