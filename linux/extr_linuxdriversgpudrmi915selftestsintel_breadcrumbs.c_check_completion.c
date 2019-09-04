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
struct intel_wait {int /*<<< orphan*/  seqno; } ;
struct intel_engine_cs {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int intel_wait_complete (struct intel_wait const*) ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ test_bit (int,unsigned long const*) ; 

__attribute__((used)) static int check_completion(struct intel_engine_cs *engine,
			    const unsigned long *bitmap,
			    const struct intel_wait *waiters,
			    const int count)
{
	int n;

	for (n = 0; n < count; n++) {
		if (intel_wait_complete(&waiters[n]) != !!test_bit(n, bitmap))
			continue;

		pr_err("waiter[%d, seqno=%d] is %s, but expected %s\n",
		       n, waiters[n].seqno,
		       intel_wait_complete(&waiters[n]) ? "complete" : "active",
		       test_bit(n, bitmap) ? "active" : "complete");
		return -EINVAL;
	}

	return 0;
}