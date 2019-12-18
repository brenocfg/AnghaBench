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
struct device {int dummy; } ;
struct apm_cmd {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  host_control_action ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 size_t smi_data_buf_realloc (int) ; 
 int /*<<< orphan*/  smi_data_lock ; 

__attribute__((used)) static ssize_t host_control_action_store(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf, size_t count)
{
	ssize_t ret;

	/* make sure buffer is available for host control command */
	mutex_lock(&smi_data_lock);
	ret = smi_data_buf_realloc(sizeof(struct apm_cmd));
	mutex_unlock(&smi_data_lock);
	if (ret)
		return ret;

	host_control_action = simple_strtoul(buf, NULL, 10);
	return count;
}