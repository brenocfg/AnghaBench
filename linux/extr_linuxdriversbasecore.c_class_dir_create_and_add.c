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
struct kobject {int /*<<< orphan*/ * kset; } ;
struct class_dir {struct kobject kobj; struct class* class; } ;
struct class {int /*<<< orphan*/  name; TYPE_1__* p; } ;
struct TYPE_2__ {int /*<<< orphan*/  glue_dirs; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct kobject* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  class_dir_ktype ; 
 int kobject_add (struct kobject*,struct kobject*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_init (struct kobject*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 
 struct class_dir* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct kobject *
class_dir_create_and_add(struct class *class, struct kobject *parent_kobj)
{
	struct class_dir *dir;
	int retval;

	dir = kzalloc(sizeof(*dir), GFP_KERNEL);
	if (!dir)
		return ERR_PTR(-ENOMEM);

	dir->class = class;
	kobject_init(&dir->kobj, &class_dir_ktype);

	dir->kobj.kset = &class->p->glue_dirs;

	retval = kobject_add(&dir->kobj, parent_kobj, "%s", class->name);
	if (retval < 0) {
		kobject_put(&dir->kobj);
		return ERR_PTR(retval);
	}
	return &dir->kobj;
}