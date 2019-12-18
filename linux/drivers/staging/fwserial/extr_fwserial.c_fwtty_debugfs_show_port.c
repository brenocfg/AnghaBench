#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stats {int /*<<< orphan*/  throttled; int /*<<< orphan*/  sent; int /*<<< orphan*/  lost; int /*<<< orphan*/  fifo_errs; int /*<<< orphan*/  tx_stall; int /*<<< orphan*/  dropped; } ;
struct seq_file {int dummy; } ;
struct TYPE_3__ {scalar_t__ console; } ;
struct fwtty_port {int /*<<< orphan*/  stats; int /*<<< orphan*/  con_data; TYPE_2__* fwcon_ops; TYPE_1__ port; } ;
typedef  int /*<<< orphan*/  stats ;
struct TYPE_4__ {int /*<<< orphan*/  (* proc_show ) (struct seq_file*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* stats ) (struct stats*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  fwtty_dump_profile (struct seq_file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct stats*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  stub1 (struct stats*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct seq_file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fwtty_debugfs_show_port(struct seq_file *m, struct fwtty_port *port)
{
	struct stats stats;

	memcpy(&stats, &port->stats, sizeof(stats));
	if (port->port.console)
		(*port->fwcon_ops->stats)(&stats, port->con_data);

	seq_printf(m, " dr:%d st:%d err:%d lost:%d", stats.dropped,
		   stats.tx_stall, stats.fifo_errs, stats.lost);
	seq_printf(m, " pkts:%d thr:%d", stats.sent, stats.throttled);

	if (port->port.console) {
		seq_puts(m, "\n    ");
		(*port->fwcon_ops->proc_show)(m, port->con_data);
	}

	fwtty_dump_profile(m, &port->stats);
}