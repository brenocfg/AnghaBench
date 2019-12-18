#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct seq_file {scalar_t__ private; } ;
struct qib_ibdev {int dummy; } ;
struct qib_devdata {size_t first_user_ctxt; TYPE_3__** rcd; } ;
typedef  size_t loff_t ;
struct TYPE_6__ {TYPE_2__* opstats; } ;
struct TYPE_5__ {TYPE_1__* stats; } ;
struct TYPE_4__ {scalar_t__ n_bytes; scalar_t__ n_packets; } ;

/* Variables and functions */
 int SEQ_SKIP ; 
 struct qib_devdata* dd_from_dev (struct qib_ibdev*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,size_t,unsigned long long,unsigned long long) ; 

__attribute__((used)) static int _opcode_stats_seq_show(struct seq_file *s, void *v)
{
	loff_t *spos = v;
	loff_t i = *spos, j;
	u64 n_packets = 0, n_bytes = 0;
	struct qib_ibdev *ibd = (struct qib_ibdev *)s->private;
	struct qib_devdata *dd = dd_from_dev(ibd);

	for (j = 0; j < dd->first_user_ctxt; j++) {
		if (!dd->rcd[j])
			continue;
		n_packets += dd->rcd[j]->opstats->stats[i].n_packets;
		n_bytes += dd->rcd[j]->opstats->stats[i].n_bytes;
	}
	if (!n_packets && !n_bytes)
		return SEQ_SKIP;
	seq_printf(s, "%02llx %llu/%llu\n", i,
		(unsigned long long) n_packets,
		(unsigned long long) n_bytes);

	return 0;
}