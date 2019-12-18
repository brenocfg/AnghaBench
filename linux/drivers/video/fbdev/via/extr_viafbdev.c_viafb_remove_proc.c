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
struct TYPE_2__ {int /*<<< orphan*/  lvds_chip_info2; int /*<<< orphan*/  lvds_chip_info; } ;
struct viafb_shared {TYPE_1__ chip_info; struct proc_dir_entry* iga1_proc_entry; struct proc_dir_entry* iga2_proc_entry; struct proc_dir_entry* proc_entry; } ;
struct proc_dir_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_VT1636 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_proc_entry (char*,struct proc_dir_entry*) ; 

__attribute__((used)) static void viafb_remove_proc(struct viafb_shared *shared)
{
	struct proc_dir_entry *viafb_entry = shared->proc_entry;

	if (!viafb_entry)
		return;

	remove_proc_entry("output_devices", shared->iga2_proc_entry);
	remove_proc_entry("iga2", viafb_entry);
	remove_proc_entry("output_devices", shared->iga1_proc_entry);
	remove_proc_entry("iga1", viafb_entry);
	remove_proc_entry("supported_output_devices", viafb_entry);

#ifdef CONFIG_FB_VIA_DIRECT_PROCFS
	remove_proc_entry("dvp0", viafb_entry);/* parent dir */
	remove_proc_entry("dvp1", viafb_entry);
	remove_proc_entry("dfph", viafb_entry);
	remove_proc_entry("dfpl", viafb_entry);
	if (IS_VT1636(shared->chip_info.lvds_chip_info)
		|| IS_VT1636(shared->chip_info.lvds_chip_info2))
		remove_proc_entry("vt1636", viafb_entry);
#endif /* CONFIG_FB_VIA_DIRECT_PROCFS */

	remove_proc_entry("viafb", NULL);
}