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
struct gb_audio_manager_module {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct gb_audio_manager_module* gb_audio_manager_get_locked (int) ; 
 int /*<<< orphan*/  kobject_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  modules_rwsem ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

struct gb_audio_manager_module *gb_audio_manager_get_module(int id)
{
	struct gb_audio_manager_module *module;

	down_read(&modules_rwsem);
	module = gb_audio_manager_get_locked(id);
	kobject_get(&module->kobj);
	up_read(&modules_rwsem);
	return module;
}