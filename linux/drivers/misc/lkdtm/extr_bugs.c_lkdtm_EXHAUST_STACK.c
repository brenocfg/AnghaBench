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
 int /*<<< orphan*/  REC_STACK_SIZE ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  recur_count ; 
 int /*<<< orphan*/  recursive_loop (int /*<<< orphan*/ ) ; 

void lkdtm_EXHAUST_STACK(void)
{
	pr_info("Calling function with %lu frame size to depth %d ...\n",
		REC_STACK_SIZE, recur_count);
	recursive_loop(recur_count);
	pr_info("FAIL: survived without exhausting stack?!\n");
}