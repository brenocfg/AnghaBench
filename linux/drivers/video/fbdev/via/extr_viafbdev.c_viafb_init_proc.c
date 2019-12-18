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
struct viafb_shared {struct proc_dir_entry* iga2_proc_entry; struct proc_dir_entry* iga1_proc_entry; TYPE_1__ chip_info; struct proc_dir_entry* proc_entry; } ;
struct proc_dir_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_VT1636 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_create (char*,int /*<<< orphan*/ ,struct proc_dir_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_create_single (char*,int /*<<< orphan*/ ,struct proc_dir_entry*,int /*<<< orphan*/ ) ; 
 struct proc_dir_entry* proc_mkdir (char*,struct proc_dir_entry*) ; 
 int /*<<< orphan*/  viafb_dfph_proc_fops ; 
 int /*<<< orphan*/  viafb_dfpl_proc_fops ; 
 int /*<<< orphan*/  viafb_dvp0_proc_fops ; 
 int /*<<< orphan*/  viafb_dvp1_proc_fops ; 
 int /*<<< orphan*/  viafb_iga1_odev_proc_fops ; 
 int /*<<< orphan*/  viafb_iga2_odev_proc_fops ; 
 int /*<<< orphan*/  viafb_sup_odev_proc_show ; 
 int /*<<< orphan*/  viafb_vt1636_proc_fops ; 

__attribute__((used)) static void viafb_init_proc(struct viafb_shared *shared)
{
	struct proc_dir_entry *iga1_entry, *iga2_entry,
		*viafb_entry = proc_mkdir("viafb", NULL);

	shared->proc_entry = viafb_entry;
	if (viafb_entry) {
#ifdef CONFIG_FB_VIA_DIRECT_PROCFS
		proc_create("dvp0", 0, viafb_entry, &viafb_dvp0_proc_fops);
		proc_create("dvp1", 0, viafb_entry, &viafb_dvp1_proc_fops);
		proc_create("dfph", 0, viafb_entry, &viafb_dfph_proc_fops);
		proc_create("dfpl", 0, viafb_entry, &viafb_dfpl_proc_fops);
		if (IS_VT1636(shared->chip_info.lvds_chip_info)
			|| IS_VT1636(shared->chip_info.lvds_chip_info2))
			proc_create("vt1636", 0, viafb_entry,
				&viafb_vt1636_proc_fops);
#endif /* CONFIG_FB_VIA_DIRECT_PROCFS */

		proc_create_single("supported_output_devices", 0, viafb_entry,
			viafb_sup_odev_proc_show);
		iga1_entry = proc_mkdir("iga1", viafb_entry);
		shared->iga1_proc_entry = iga1_entry;
		proc_create("output_devices", 0, iga1_entry,
			&viafb_iga1_odev_proc_fops);
		iga2_entry = proc_mkdir("iga2", viafb_entry);
		shared->iga2_proc_entry = iga2_entry;
		proc_create("output_devices", 0, iga2_entry,
			&viafb_iga2_odev_proc_fops);
	}
}