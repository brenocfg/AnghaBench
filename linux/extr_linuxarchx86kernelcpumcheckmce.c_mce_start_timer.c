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
struct timer_list {int dummy; } ;
struct TYPE_2__ {scalar_t__ ignore_ce; } ;

/* Variables and functions */
 unsigned long HZ ; 
 int /*<<< orphan*/  __start_timer (struct timer_list*,unsigned long) ; 
 unsigned long check_interval ; 
 TYPE_1__ mca_cfg ; 
 int /*<<< orphan*/  mce_next_interval ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void mce_start_timer(struct timer_list *t)
{
	unsigned long iv = check_interval * HZ;

	if (mca_cfg.ignore_ce || !iv)
		return;

	this_cpu_write(mce_next_interval, iv);
	__start_timer(t, iv);
}