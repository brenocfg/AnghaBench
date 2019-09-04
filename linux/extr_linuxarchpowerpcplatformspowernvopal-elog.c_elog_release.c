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
struct elog_obj {struct elog_obj* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct elog_obj*) ; 
 struct elog_obj* to_elog_obj (struct kobject*) ; 

__attribute__((used)) static void elog_release(struct kobject *kobj)
{
	struct elog_obj *elog;

	elog = to_elog_obj(kobj);
	kfree(elog->buffer);
	kfree(elog);
}