#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {TYPE_1__* action; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 TYPE_2__ on_panic_trigger ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t on_panic_show(struct kobject *kobj,
			     struct kobj_attribute *attr, char *page)
{
	return sprintf(page, "%s\n", on_panic_trigger.action->name);
}