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
struct vc4_perfmon {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vc4_perfmon*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

void vc4_perfmon_put(struct vc4_perfmon *perfmon)
{
	if (perfmon && refcount_dec_and_test(&perfmon->refcnt))
		kfree(perfmon);
}