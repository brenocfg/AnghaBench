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
struct fwtty_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int MAX_TOTAL_PORTS ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 struct fwtty_port* fwtty_port_get (int) ; 
 int /*<<< orphan*/  fwtty_port_put (struct fwtty_port*) ; 
 int /*<<< orphan*/  fwtty_proc_show_port (struct seq_file*,struct fwtty_port*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int fwtty_proc_show(struct seq_file *m, void *v)
{
	struct fwtty_port *port;
	int i;

	seq_puts(m, "fwserinfo: 1.0 driver: 1.0\n");
	for (i = 0; i < MAX_TOTAL_PORTS && (port = fwtty_port_get(i)); ++i) {
		seq_printf(m, "%2d:", i);
		if (capable(CAP_SYS_ADMIN))
			fwtty_proc_show_port(m, port);
		fwtty_port_put(port);
		seq_puts(m, "\n");
	}
	return 0;
}