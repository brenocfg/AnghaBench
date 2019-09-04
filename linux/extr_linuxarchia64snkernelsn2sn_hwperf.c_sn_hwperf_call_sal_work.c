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
 int /*<<< orphan*/  sn_hwperf_call_sal (void*) ; 

__attribute__((used)) static long sn_hwperf_call_sal_work(void *info)
{
	sn_hwperf_call_sal(info);
	return 0;
}