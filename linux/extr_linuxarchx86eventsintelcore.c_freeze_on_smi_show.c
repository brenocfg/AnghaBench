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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  attr_freeze_on_smi; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static ssize_t freeze_on_smi_show(struct device *cdev,
				  struct device_attribute *attr,
				  char *buf)
{
	return sprintf(buf, "%lu\n", x86_pmu.attr_freeze_on_smi);
}