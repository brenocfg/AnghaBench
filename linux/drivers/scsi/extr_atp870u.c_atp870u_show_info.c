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
struct seq_file {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  irq; int /*<<< orphan*/  io_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int atp870u_show_info(struct seq_file *m, struct Scsi_Host *HBAptr)
{
	seq_puts(m, "ACARD AEC-671X Driver Version: 2.6+ac\n\n"
		"Adapter Configuration:\n");
	seq_printf(m, "               Base IO: %#.4lx\n", HBAptr->io_port);
	seq_printf(m, "                   IRQ: %d\n", HBAptr->irq);
	return 0;
}