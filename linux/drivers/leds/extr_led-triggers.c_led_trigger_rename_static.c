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
struct led_trigger {char const* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int /*<<< orphan*/  triggers_list_lock ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void led_trigger_rename_static(const char *name, struct led_trigger *trig)
{
	/* new name must be on a temporary string to prevent races */
	BUG_ON(name == trig->name);

	down_write(&triggers_list_lock);
	/* this assumes that trig->name was originaly allocated to
	 * non constant storage */
	strcpy((char *)trig->name, name);
	up_write(&triggers_list_lock);
}