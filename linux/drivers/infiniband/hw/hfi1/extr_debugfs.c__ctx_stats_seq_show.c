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
struct seq_file {scalar_t__ private; } ;
struct hfi1_ibdev {int dummy; } ;
struct hfi1_devdata {int dummy; } ;
struct hfi1_ctxtdata {TYPE_1__* opstats; } ;
typedef  size_t loff_t ;
struct TYPE_4__ {scalar_t__ n_packets; } ;
struct TYPE_3__ {TYPE_2__* stats; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_2__*) ; 
 int SEQ_SKIP ; 
 void* SEQ_START_TOKEN ; 
 struct hfi1_devdata* dd_from_dev (struct hfi1_ibdev*) ; 
 struct hfi1_ctxtdata* hfi1_rcd_get_by_index_safe (struct hfi1_devdata*,size_t) ; 
 int /*<<< orphan*/  hfi1_rcd_put (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int _ctx_stats_seq_show(struct seq_file *s, void *v)
{
	loff_t *spos;
	loff_t i, j;
	u64 n_packets = 0;
	struct hfi1_ibdev *ibd = (struct hfi1_ibdev *)s->private;
	struct hfi1_devdata *dd = dd_from_dev(ibd);
	struct hfi1_ctxtdata *rcd;

	if (v == SEQ_START_TOKEN) {
		seq_puts(s, "Ctx:npkts\n");
		return 0;
	}

	spos = v;
	i = *spos;

	rcd = hfi1_rcd_get_by_index_safe(dd, i);
	if (!rcd)
		return SEQ_SKIP;

	for (j = 0; j < ARRAY_SIZE(rcd->opstats->stats); j++)
		n_packets += rcd->opstats->stats[j].n_packets;

	hfi1_rcd_put(rcd);

	if (!n_packets)
		return SEQ_SKIP;

	seq_printf(s, "  %llu:%llu\n", i, n_packets);
	return 0;
}