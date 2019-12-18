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
struct seq_file {int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int proc_print_scsidevice (void*,struct seq_file*) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int scsi_seq_show(struct seq_file *sfile, void *dev)
{
	if (!sfile->private)
		seq_puts(sfile, "Attached devices:\n");

	return proc_print_scsidevice(dev, sfile);
}