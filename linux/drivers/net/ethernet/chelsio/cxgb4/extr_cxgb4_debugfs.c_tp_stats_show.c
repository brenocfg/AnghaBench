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
struct seq_file {struct adapter* private; } ;
struct TYPE_3__ {scalar_t__ nchan; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;
struct adapter {TYPE_2__ params; } ;

/* Variables and functions */
 scalar_t__ NCHAN ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  show_cpl_stats (struct seq_file*) ; 
 int /*<<< orphan*/  show_ddp_stats (struct seq_file*) ; 
 int /*<<< orphan*/  show_fcoe_stats (struct seq_file*) ; 
 int /*<<< orphan*/  show_rdma_stats (struct seq_file*) ; 
 int /*<<< orphan*/  show_tcp_stats (struct seq_file*) ; 
 int /*<<< orphan*/  show_tp_err_adapter_stats (struct seq_file*) ; 
 int /*<<< orphan*/  show_tp_err_channel_stats (struct seq_file*) ; 

__attribute__((used)) static int tp_stats_show(struct seq_file *seq, void *v)
{
	struct adapter *adap = seq->private;

	seq_puts(seq, "\n--------Adapter Stats--------\n");
	show_tcp_stats(seq);
	show_ddp_stats(seq);
	show_rdma_stats(seq);
	show_tp_err_adapter_stats(seq);

	seq_puts(seq, "\n-------- Channel Stats --------\n");
	if (adap->params.arch.nchan == NCHAN)
		seq_printf(seq, "%-25s %-20s %-20s %-20s %-20s\n",
			   " ", "channel 0", "channel 1",
			   "channel 2", "channel 3");
	else
		seq_printf(seq, "%-25s %-20s %-20s\n",
			   " ", "channel 0", "channel 1");
	show_cpl_stats(seq);
	show_tp_err_channel_stats(seq);
	show_fcoe_stats(seq);

	return 0;
}