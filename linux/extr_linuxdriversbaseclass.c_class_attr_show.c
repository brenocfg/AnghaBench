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
struct subsys_private {int /*<<< orphan*/  class; } ;
struct kobject {int dummy; } ;
struct class_attribute {int /*<<< orphan*/  (* show ) (int /*<<< orphan*/ ,struct class_attribute*,char*) ;} ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct class_attribute*,char*) ; 
 struct class_attribute* to_class_attr (struct attribute*) ; 
 struct subsys_private* to_subsys_private (struct kobject*) ; 

__attribute__((used)) static ssize_t class_attr_show(struct kobject *kobj, struct attribute *attr,
			       char *buf)
{
	struct class_attribute *class_attr = to_class_attr(attr);
	struct subsys_private *cp = to_subsys_private(kobj);
	ssize_t ret = -EIO;

	if (class_attr->show)
		ret = class_attr->show(cp->class, class_attr, buf);
	return ret;
}