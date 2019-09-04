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
struct device {int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  read_mmustat_enable ; 
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 
 long work_on_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t show_mmustat_enable(struct device *s,
				struct device_attribute *attr, char *buf)
{
	long val = work_on_cpu(s->id, read_mmustat_enable, NULL);

	return sprintf(buf, "%lx\n", val);
}