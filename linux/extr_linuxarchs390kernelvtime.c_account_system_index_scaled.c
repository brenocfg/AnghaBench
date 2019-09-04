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
typedef  int /*<<< orphan*/  u64 ;
struct task_struct {int /*<<< orphan*/  stimescaled; } ;
typedef  enum cpu_usage_stat { ____Placeholder_cpu_usage_stat } cpu_usage_stat ;

/* Variables and functions */
 int /*<<< orphan*/  account_system_index_time (struct task_struct*,scalar_t__,int) ; 
 scalar_t__ cputime_to_nsecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scale_vtime (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void account_system_index_scaled(struct task_struct *p, u64 cputime,
					enum cpu_usage_stat index)
{
	p->stimescaled += cputime_to_nsecs(scale_vtime(cputime));
	account_system_index_time(p, cputime_to_nsecs(cputime), index);
}