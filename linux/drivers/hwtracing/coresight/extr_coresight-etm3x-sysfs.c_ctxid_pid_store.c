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
struct etm_config {unsigned long* ctxid_pid; size_t ctxid_idx; } ;
struct etm_drvdata {int /*<<< orphan*/  spinlock; struct etm_config config; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  current ; 
 struct etm_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_pid_ns ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * task_active_pid_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t ctxid_pid_store(struct device *dev,
			       struct device_attribute *attr,
			       const char *buf, size_t size)
{
	int ret;
	unsigned long pid;
	struct etm_drvdata *drvdata = dev_get_drvdata(dev->parent);
	struct etm_config *config = &drvdata->config;

	/*
	 * When contextID tracing is enabled the tracers will insert the
	 * value found in the contextID register in the trace stream.  But if
	 * a process is in a namespace the PID of that process as seen from the
	 * namespace won't be what the kernel sees, something that makes the
	 * feature confusing and can potentially leak kernel only information.
	 * As such refuse to use the feature if @current is not in the initial
	 * PID namespace.
	 */
	if (task_active_pid_ns(current) != &init_pid_ns)
		return -EINVAL;

	ret = kstrtoul(buf, 16, &pid);
	if (ret)
		return ret;

	spin_lock(&drvdata->spinlock);
	config->ctxid_pid[config->ctxid_idx] = pid;
	spin_unlock(&drvdata->spinlock);

	return size;
}