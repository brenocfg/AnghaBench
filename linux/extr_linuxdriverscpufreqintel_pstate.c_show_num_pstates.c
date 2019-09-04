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
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
struct TYPE_2__ {int turbo_pstate; int min_pstate; } ;
struct cpudata {TYPE_1__ pstate; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 struct cpudata** all_cpu_data ; 
 int /*<<< orphan*/  intel_pstate_driver ; 
 int /*<<< orphan*/  intel_pstate_driver_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_num_pstates(struct kobject *kobj,
				struct kobj_attribute *attr, char *buf)
{
	struct cpudata *cpu;
	int total;

	mutex_lock(&intel_pstate_driver_lock);

	if (!intel_pstate_driver) {
		mutex_unlock(&intel_pstate_driver_lock);
		return -EAGAIN;
	}

	cpu = all_cpu_data[0];
	total = cpu->pstate.turbo_pstate - cpu->pstate.min_pstate + 1;

	mutex_unlock(&intel_pstate_driver_lock);

	return sprintf(buf, "%u\n", total);
}