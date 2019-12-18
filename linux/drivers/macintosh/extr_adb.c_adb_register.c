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
struct adb_ids {int nids; int* id; } ;
struct TYPE_2__ {int original_address; int handler_id; void (* handler ) (unsigned char*,int,int) ;} ;

/* Variables and functions */
 TYPE_1__* adb_handler ; 
 int /*<<< orphan*/  adb_handler_lock ; 
 int /*<<< orphan*/  adb_handler_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 scalar_t__ try_handler_change (int,int) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

int
adb_register(int default_id, int handler_id, struct adb_ids *ids,
	     void (*handler)(unsigned char *, int, int))
{
	int i;

	mutex_lock(&adb_handler_mutex);
	ids->nids = 0;
	for (i = 1; i < 16; i++) {
		if ((adb_handler[i].original_address == default_id) &&
		    (!handler_id || (handler_id == adb_handler[i].handler_id) || 
		    try_handler_change(i, handler_id))) {
			if (adb_handler[i].handler != 0) {
				pr_err("Two handlers for ADB device %d\n",
				       default_id);
				continue;
			}
			write_lock_irq(&adb_handler_lock);
			adb_handler[i].handler = handler;
			write_unlock_irq(&adb_handler_lock);
			ids->id[ids->nids++] = i;
		}
	}
	mutex_unlock(&adb_handler_mutex);
	return ids->nids;
}