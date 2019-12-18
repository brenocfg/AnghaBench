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
typedef  scalar_t__ u64 ;
struct seq_file {struct adapter* private; } ;
struct TYPE_3__ {int nchan; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;
struct adapter {TYPE_2__ params; } ;

/* Variables and functions */
 int NCHAN ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned long long,unsigned long long,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  t4_get_chan_txrate (struct adapter*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int tx_rate_show(struct seq_file *seq, void *v)
{
	u64 nrate[NCHAN], orate[NCHAN];
	struct adapter *adap = seq->private;

	t4_get_chan_txrate(adap, nrate, orate);
	if (adap->params.arch.nchan == NCHAN) {
		seq_puts(seq, "              channel 0   channel 1   "
			 "channel 2   channel 3\n");
		seq_printf(seq, "NIC B/s:     %10llu  %10llu  %10llu  %10llu\n",
			   (unsigned long long)nrate[0],
			   (unsigned long long)nrate[1],
			   (unsigned long long)nrate[2],
			   (unsigned long long)nrate[3]);
		seq_printf(seq, "Offload B/s: %10llu  %10llu  %10llu  %10llu\n",
			   (unsigned long long)orate[0],
			   (unsigned long long)orate[1],
			   (unsigned long long)orate[2],
			   (unsigned long long)orate[3]);
	} else {
		seq_puts(seq, "              channel 0   channel 1\n");
		seq_printf(seq, "NIC B/s:     %10llu  %10llu\n",
			   (unsigned long long)nrate[0],
			   (unsigned long long)nrate[1]);
		seq_printf(seq, "Offload B/s: %10llu  %10llu\n",
			   (unsigned long long)orate[0],
			   (unsigned long long)orate[1]);
	}
	return 0;
}