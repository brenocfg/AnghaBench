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
 int /*<<< orphan*/  pr_info (char*) ; 
 int test_kprobe (long (*) (long,long)) ; 
 int test_kretprobe (long (*) (long,long)) ; 

__attribute__((used)) static int run_api_tests(long (*func)(long, long))
{
	int ret;

	pr_info("    kprobe\n");
	ret = test_kprobe(func);
	if (ret < 0)
		return ret;

	pr_info("    kretprobe\n");
	ret = test_kretprobe(func);
	if (ret < 0)
		return ret;

	return 0;
}