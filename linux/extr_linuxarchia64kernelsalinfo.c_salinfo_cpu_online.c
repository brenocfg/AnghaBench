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
struct salinfo_data {int /*<<< orphan*/  read_wait; int /*<<< orphan*/  cpu_event; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct salinfo_data*) ; 
 int /*<<< orphan*/  cpumask_set_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  data_saved_lock ; 
 struct salinfo_data* salinfo_data ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int salinfo_cpu_online(unsigned int cpu)
{
	unsigned int i, end = ARRAY_SIZE(salinfo_data);
	struct salinfo_data *data;

	spin_lock_irq(&data_saved_lock);
	for (i = 0, data = salinfo_data; i < end; ++i, ++data) {
		cpumask_set_cpu(cpu, &data->cpu_event);
		wake_up_interruptible(&data->read_wait);
	}
	spin_unlock_irq(&data_saved_lock);
	return 0;
}