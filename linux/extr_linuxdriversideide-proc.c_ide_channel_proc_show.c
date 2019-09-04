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
struct TYPE_2__ {scalar_t__ channel; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char) ; 

__attribute__((used)) static int ide_channel_proc_show(struct seq_file *m, void *v)
{
	ide_hwif_t	*hwif = (ide_hwif_t *) m->private;

	seq_printf(m, "%c\n", hwif->channel ? '1' : '0');
	return 0;
}