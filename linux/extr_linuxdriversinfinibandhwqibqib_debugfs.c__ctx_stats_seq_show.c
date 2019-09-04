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
struct qib_devdata {TYPE_2__** rcd; } ;
typedef  size_t loff_t ;
struct TYPE_6__ {scalar_t__ n_packets; } ;
struct TYPE_5__ {TYPE_1__* opstats; } ;
struct TYPE_4__ {TYPE_3__* stats; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_3__*) ; 
 int SEQ_SKIP ; 
 void* SEQ_START_TOKEN ; 
 struct qib_devdata* dd_from_dev (struct qib_ibdev*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int _ctx_stats_seq_show(struct seq_file *s, void *v)
{
	loff_t *spos;
	loff_t i, j;
	u64 n_packets = 0;
	struct qib_ibdev *ibd = (struct qib_ibdev *)s->private;
	struct qib_devdata *dd = dd_from_dev(ibd);

	if (v == SEQ_START_TOKEN) {
		seq_puts(s, "Ctx:npkts\n");
		return 0;
	}

	spos = v;
	i = *spos;

	if (!dd->rcd[i])
		return SEQ_SKIP;

	for (j = 0; j < ARRAY_SIZE(dd->rcd[i]->opstats->stats); j++)
		n_packets += dd->rcd[i]->opstats->stats[j].n_packets;

	if (!n_packets)
		return SEQ_SKIP;

	seq_printf(s, "  %llu:%llu\n", i, n_packets);
	return 0;
}