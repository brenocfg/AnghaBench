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
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int sprintf (char*,char*,char*) ; 
 TYPE_1__* synth ; 

__attribute__((used)) static ssize_t synth_show(struct kobject *kobj, struct kobj_attribute *attr,
			  char *buf)
{
	int rv;

	if (!synth)
		rv = sprintf(buf, "%s\n", "none");
	else
		rv = sprintf(buf, "%s\n", synth->name);
	return rv;
}