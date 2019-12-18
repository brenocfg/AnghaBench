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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int lb_interval_jiffies ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,unsigned long) ; 

__attribute__((used)) static ssize_t interval_msec_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	unsigned long msec = lb_interval_jiffies * 1000 / HZ;

	return scnprintf(buf, PAGE_SIZE, "%lu\n", msec);
}