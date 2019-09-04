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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 scalar_t__ probe_task ; 

__attribute__((used)) static int ps3_stop_probe_thread(struct notifier_block *nb, unsigned long code,
				 void *data)
{
	if (probe_task)
		kthread_stop(probe_task);
	return 0;
}