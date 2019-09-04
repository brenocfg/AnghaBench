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
struct device_attribute {int dummy; } ;
struct device {int id; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_cpu_state_mutex ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int topology_cpu_dedicated (int) ; 

__attribute__((used)) static ssize_t cpu_dedicated_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	int cpu = dev->id;
	ssize_t count;

	mutex_lock(&smp_cpu_state_mutex);
	count = sprintf(buf, "%d\n", topology_cpu_dedicated(cpu));
	mutex_unlock(&smp_cpu_state_mutex);
	return count;
}