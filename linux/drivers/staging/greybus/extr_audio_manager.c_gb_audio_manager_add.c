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
struct gb_audio_manager_module_descriptor {int dummy; } ;
struct gb_audio_manager_module {int id; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int gb_audio_manager_module_create (struct gb_audio_manager_module**,int /*<<< orphan*/ ,int,struct gb_audio_manager_module_descriptor*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  manager_kset ; 
 int /*<<< orphan*/  module_id ; 
 int /*<<< orphan*/  modules_list ; 
 int /*<<< orphan*/  modules_rwsem ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int gb_audio_manager_add(struct gb_audio_manager_module_descriptor *desc)
{
	struct gb_audio_manager_module *module;
	int id;
	int err;

	id = ida_simple_get(&module_id, 0, 0, GFP_KERNEL);
	if (id < 0)
		return id;

	err = gb_audio_manager_module_create(&module, manager_kset,
					     id, desc);
	if (err) {
		ida_simple_remove(&module_id, id);
		return err;
	}

	/* Add it to the list */
	down_write(&modules_rwsem);
	list_add_tail(&module->list, &modules_list);
	up_write(&modules_rwsem);

	return module->id;
}