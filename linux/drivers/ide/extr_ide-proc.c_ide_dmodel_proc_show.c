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
struct TYPE_2__ {int /*<<< orphan*/ * id; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 size_t ATA_ID_PROD ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 

__attribute__((used)) static int ide_dmodel_proc_show(struct seq_file *seq, void *v)
{
	ide_drive_t	*drive = (ide_drive_t *) seq->private;
	char		*m = (char *)&drive->id[ATA_ID_PROD];

	seq_printf(seq, "%.40s\n", m[0] ? m : "(none)");
	return 0;
}