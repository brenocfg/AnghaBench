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
struct pdcspath_entry {int dummy; } ;
struct pdcspath_attribute {int /*<<< orphan*/  (* show ) (struct pdcspath_entry*,char*) ;} ;
struct kobject {int dummy; } ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct pdcspath_entry*,char*) ; 
 struct pdcspath_attribute* to_pdcspath_attribute (struct attribute*) ; 
 struct pdcspath_entry* to_pdcspath_entry (struct kobject*) ; 

__attribute__((used)) static ssize_t
pdcspath_attr_show(struct kobject *kobj, struct attribute *attr, char *buf)
{
	struct pdcspath_entry *entry = to_pdcspath_entry(kobj);
	struct pdcspath_attribute *pdcs_attr = to_pdcspath_attribute(attr);
	ssize_t ret = 0;

	if (pdcs_attr->show)
		ret = pdcs_attr->show(entry, buf);

	return ret;
}