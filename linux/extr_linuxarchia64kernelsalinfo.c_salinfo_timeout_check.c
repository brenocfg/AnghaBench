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
struct salinfo_data {int /*<<< orphan*/  read_wait; int /*<<< orphan*/  cpu_event; int /*<<< orphan*/  open; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
salinfo_timeout_check(struct salinfo_data *data)
{
	if (!data->open)
		return;
	if (!cpumask_empty(&data->cpu_event))
		wake_up_interruptible(&data->read_wait);
}