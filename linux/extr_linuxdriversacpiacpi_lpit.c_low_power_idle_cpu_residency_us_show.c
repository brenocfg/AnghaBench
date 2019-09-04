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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int lpit_read_residency_counter_us (int /*<<< orphan*/ *,int) ; 
 int sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t low_power_idle_cpu_residency_us_show(struct device *dev,
						    struct device_attribute *attr,
						    char *buf)
{
	u64 counter;
	int ret;

	ret = lpit_read_residency_counter_us(&counter, false);
	if (ret)
		return ret;

	return sprintf(buf, "%llu\n", counter);
}