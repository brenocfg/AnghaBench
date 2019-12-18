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
typedef  int umode_t ;
struct kobject {int dummy; } ;
struct attribute {int mode; } ;
struct TYPE_2__ {struct attribute attr; } ;

/* Variables and functions */
 TYPE_1__ dev_attr_resource ; 

__attribute__((used)) static umode_t pfn_visible(struct kobject *kobj, struct attribute *a, int n)
{
	if (a == &dev_attr_resource.attr)
		return 0400;
	return a->mode;
}