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
struct host1x_syncpt {int /*<<< orphan*/  max_val; int /*<<< orphan*/  min_val; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static inline bool host1x_syncpt_idle(struct host1x_syncpt *sp)
{
	int min, max;
	smp_rmb();
	min = atomic_read(&sp->min_val);
	max = atomic_read(&sp->max_val);
	return (min == max);
}