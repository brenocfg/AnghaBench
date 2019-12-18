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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESCAPE_CODE ; 
 int /*<<< orphan*/  MODULE_LOADED_CODE ; 
 unsigned long MODULE_STATE_COMING ; 
 int /*<<< orphan*/  add_event_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
module_load_notify(struct notifier_block *self, unsigned long val, void *data)
{
#ifdef CONFIG_MODULES
	if (val != MODULE_STATE_COMING)
		return 0;

	/* FIXME: should we process all CPU buffers ? */
	mutex_lock(&buffer_mutex);
	add_event_entry(ESCAPE_CODE);
	add_event_entry(MODULE_LOADED_CODE);
	mutex_unlock(&buffer_mutex);
#endif
	return 0;
}