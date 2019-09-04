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
struct attribute {char* name; int mode; } ;
struct TYPE_2__ {struct attribute attr; int /*<<< orphan*/  show; } ;
struct dev_ext_attribute {char* var; TYPE_1__ attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  device_show_string ; 
 struct dev_ext_attribute* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_attr_init (struct attribute*) ; 

__attribute__((used)) static struct attribute *device_str_attr_create_(char *name, char *str)
{
	struct dev_ext_attribute *attr = kzalloc(sizeof(*attr), GFP_KERNEL);

	if (!attr)
		return NULL;

	sysfs_attr_init(&attr->attr.attr);

	attr->var = str;
	attr->attr.attr.name = name;
	attr->attr.attr.mode = 0444;
	attr->attr.show = device_show_string;

	return &attr->attr.attr;
}