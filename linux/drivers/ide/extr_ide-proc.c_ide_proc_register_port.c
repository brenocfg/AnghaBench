#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ proc; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 int /*<<< orphan*/  hwif_entries ; 
 int /*<<< orphan*/  ide_add_proc_entries (scalar_t__,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  proc_ide_root ; 
 scalar_t__ proc_mkdir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ide_proc_register_port(ide_hwif_t *hwif)
{
	if (!hwif->proc) {
		hwif->proc = proc_mkdir(hwif->name, proc_ide_root);

		if (!hwif->proc)
			return;

		ide_add_proc_entries(hwif->proc, hwif_entries, hwif);
	}
}