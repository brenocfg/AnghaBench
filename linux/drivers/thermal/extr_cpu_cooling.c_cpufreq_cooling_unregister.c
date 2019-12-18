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
struct thermal_cooling_device {struct cpufreq_cooling_device* devdata; } ;
struct cpufreq_cooling_device {struct cpufreq_cooling_device* freq_table; struct cpufreq_cooling_device* idle_time; int /*<<< orphan*/  id; int /*<<< orphan*/  qos_req; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  cooling_list_lock ; 
 int /*<<< orphan*/  cpufreq_ida ; 
 int /*<<< orphan*/  freq_qos_remove_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cpufreq_cooling_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thermal_cooling_device_unregister (struct thermal_cooling_device*) ; 

void cpufreq_cooling_unregister(struct thermal_cooling_device *cdev)
{
	struct cpufreq_cooling_device *cpufreq_cdev;

	if (!cdev)
		return;

	cpufreq_cdev = cdev->devdata;

	mutex_lock(&cooling_list_lock);
	list_del(&cpufreq_cdev->node);
	mutex_unlock(&cooling_list_lock);

	thermal_cooling_device_unregister(cdev);
	freq_qos_remove_request(&cpufreq_cdev->qos_req);
	ida_simple_remove(&cpufreq_ida, cpufreq_cdev->id);
	kfree(cpufreq_cdev->idle_time);
	kfree(cpufreq_cdev->freq_table);
	kfree(cpufreq_cdev);
}