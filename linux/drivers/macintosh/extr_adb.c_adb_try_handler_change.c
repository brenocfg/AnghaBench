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

/* Variables and functions */
 int /*<<< orphan*/  adb_handler_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 int try_handler_change (int,int) ; 

int
adb_try_handler_change(int address, int new_id)
{
	int ret;

	mutex_lock(&adb_handler_mutex);
	ret = try_handler_change(address, new_id);
	mutex_unlock(&adb_handler_mutex);
	if (ret)
		pr_debug("adb handler change: [%d] 0x%X\n", address, new_id);
	return ret;
}