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
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
struct afu_config_record {int /*<<< orphan*/  class; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct afu_config_record* to_cr (struct kobject*) ; 

__attribute__((used)) static ssize_t class_show(struct kobject *kobj,
			  struct kobj_attribute *attr, char *buf)
{
	struct afu_config_record *cr = to_cr(kobj);

	return scnprintf(buf, PAGE_SIZE, "0x%.6x\n", cr->class);
}