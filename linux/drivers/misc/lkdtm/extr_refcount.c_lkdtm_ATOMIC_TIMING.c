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
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_INIT (int) ; 
 int INT_MAX ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

void lkdtm_ATOMIC_TIMING(void)
{
	unsigned int i;
	atomic_t count = ATOMIC_INIT(1);

	for (i = 0; i < INT_MAX - 1; i++)
		atomic_inc(&count);

	for (i = INT_MAX; i > 0; i--)
		if (atomic_dec_and_test(&count))
			break;

	if (i != 1)
		pr_err("atomic timing: out of sync up/down cycle: %u\n", i - 1);
	else
		pr_info("atomic timing: done\n");
}