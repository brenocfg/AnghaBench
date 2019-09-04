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
struct TYPE_3__ {int /*<<< orphan*/  show; int /*<<< orphan*/  mode; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ ide_proc_entry_t ;

/* Variables and functions */
 struct proc_dir_entry* proc_create_single_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct proc_dir_entry*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void ide_add_proc_entries(struct proc_dir_entry *dir, ide_proc_entry_t *p, void *data)
{
	struct proc_dir_entry *ent;

	if (!dir || !p)
		return;
	while (p->name != NULL) {
		ent = proc_create_single_data(p->name, p->mode, dir, p->show, data);
		if (!ent) return;
		p++;
	}
}