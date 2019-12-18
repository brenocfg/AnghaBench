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
struct seq_file {struct fw_serial* private; } ;
struct fwtty_port {int /*<<< orphan*/  index; } ;
struct fw_serial {TYPE_1__** ports; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  fwtty_debugfs_show_port (struct seq_file*,struct fwtty_port*) ; 
 struct fwtty_port* fwtty_port_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwtty_port_put (struct fwtty_port*) ; 
 int /*<<< orphan*/  fwtty_proc_show_port (struct seq_file*,struct fwtty_port*) ; 
 int num_ports ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int fwtty_stats_show(struct seq_file *m, void *v)
{
	struct fw_serial *serial = m->private;
	struct fwtty_port *port;
	int i;

	for (i = 0; i < num_ports; ++i) {
		port = fwtty_port_get(serial->ports[i]->index);
		if (port) {
			seq_printf(m, "%2d:", port->index);
			fwtty_proc_show_port(m, port);
			fwtty_debugfs_show_port(m, port);
			fwtty_port_put(port);
			seq_puts(m, "\n");
		}
	}
	return 0;
}