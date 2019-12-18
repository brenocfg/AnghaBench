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
 int /*<<< orphan*/  ide_drivers_fops ; 
 int /*<<< orphan*/  proc_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_ide_root ; 
 int /*<<< orphan*/  proc_mkdir (char*,int /*<<< orphan*/ *) ; 

void proc_ide_create(void)
{
	proc_ide_root = proc_mkdir("ide", NULL);

	if (!proc_ide_root)
		return;

	proc_create("drivers", 0, proc_ide_root, &ide_drivers_fops);
}