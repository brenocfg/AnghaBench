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
struct target_type {int /*<<< orphan*/  list; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DMCRIT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __find_target_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _lock ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void dm_unregister_target(struct target_type *tt)
{
	down_write(&_lock);
	if (!__find_target_type(tt->name)) {
		DMCRIT("Unregistering unrecognised target: %s", tt->name);
		BUG();
	}

	list_del(&tt->list);

	up_write(&_lock);
}