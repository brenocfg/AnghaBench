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
struct seq_file {scalar_t__ private; } ;
struct TYPE_2__ {int dev_flags; int* id; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 size_t ATA_ID_BUF_SIZE ; 
 int IDE_DFLAG_ID_READ ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int idedisk_cache_proc_show(struct seq_file *m, void *v)
{
	ide_drive_t	*drive = (ide_drive_t *) m->private;

	if (drive->dev_flags & IDE_DFLAG_ID_READ)
		seq_printf(m, "%i\n", drive->id[ATA_ID_BUF_SIZE] / 2);
	else
		seq_printf(m, "(none)\n");
	return 0;
}