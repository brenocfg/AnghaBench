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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PF_AUTOSEARCH ; 
 int /*<<< orphan*/  pdcs_auto_read (struct kobject*,struct kobj_attribute*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t pdcs_autosearch_read(struct kobject *kobj,
				    struct kobj_attribute *attr, char *buf)
{
	return pdcs_auto_read(kobj, attr, buf, PF_AUTOSEARCH);
}