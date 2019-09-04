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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 int /*<<< orphan*/  xcall_deliver (int,int,int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void smp_cross_call_masked(unsigned long *func, u32 ctx, u64 data1, u64 data2, const cpumask_t *mask)
{
	u64 data0 = (((u64)ctx)<<32 | (((u64)func) & 0xffffffff));

	xcall_deliver(data0, data1, data2, mask);
}