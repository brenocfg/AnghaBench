#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct proc_dir_entry {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ ide_proc_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ *,struct proc_dir_entry*) ; 

__attribute__((used)) static void ide_remove_proc_entries(struct proc_dir_entry *dir, ide_proc_entry_t *p)
{
	if (!dir || !p)
		return;
	while (p->name != NULL) {
		remove_proc_entry(p->name, dir);
		p++;
	}
}