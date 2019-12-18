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
struct gb_audio_manager_module {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct gb_audio_manager_module* gb_audio_manager_get_locked (int) ; 
 int /*<<< orphan*/  gb_audio_manager_module_dump (struct gb_audio_manager_module*) ; 
 int /*<<< orphan*/  modules_rwsem ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int gb_audio_manager_dump_module(int id)
{
	struct gb_audio_manager_module *module;

	down_read(&modules_rwsem);
	module = gb_audio_manager_get_locked(id);
	up_read(&modules_rwsem);

	if (!module)
		return -EINVAL;

	gb_audio_manager_module_dump(module);
	return 0;
}