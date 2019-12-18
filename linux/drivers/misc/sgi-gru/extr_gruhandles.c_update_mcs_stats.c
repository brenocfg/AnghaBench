#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum mcs_op { ____Placeholder_mcs_op } mcs_op ;
struct TYPE_2__ {unsigned long max; int /*<<< orphan*/  total; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 unsigned long CLKS2NSEC (unsigned long) ; 
 int /*<<< orphan*/  atomic_long_add (unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 TYPE_1__* mcs_op_statistics ; 

__attribute__((used)) static void update_mcs_stats(enum mcs_op op, unsigned long clks)
{
	unsigned long nsec;

	nsec = CLKS2NSEC(clks);
	atomic_long_inc(&mcs_op_statistics[op].count);
	atomic_long_add(nsec, &mcs_op_statistics[op].total);
	if (mcs_op_statistics[op].max < nsec)
		mcs_op_statistics[op].max = nsec;
}