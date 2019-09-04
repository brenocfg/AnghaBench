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
 int /*<<< orphan*/  adb_probe_mutex ; 
 int /*<<< orphan*/  do_adb_reset_bus () ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
adb_probe_task(void *x)
{
	pr_debug("adb: starting probe task...\n");
	do_adb_reset_bus();
	pr_debug("adb: finished probe task...\n");

	up(&adb_probe_mutex);

	return 0;
}