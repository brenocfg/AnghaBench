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
typedef  int /*<<< orphan*/  u64 ;
struct seq_file {scalar_t__ private; } ;
struct hfi1_ibdev {int dummy; } ;
struct hfi1_devdata {scalar_t__ first_dyn_alloc_ctxt; } ;
struct hfi1_ctxtdata {TYPE_2__* opstats; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_4__ {TYPE_1__* stats; } ;
struct TYPE_3__ {scalar_t__ n_bytes; scalar_t__ n_packets; } ;

/* Variables and functions */
 struct hfi1_devdata* dd_from_dev (struct hfi1_ibdev*) ; 
 struct hfi1_ctxtdata* hfi1_rcd_get_by_index (struct hfi1_devdata*,scalar_t__) ; 
 int /*<<< orphan*/  hfi1_rcd_put (struct hfi1_ctxtdata*) ; 
 int opcode_stats_show (struct seq_file*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _opcode_stats_seq_show(struct seq_file *s, void *v)
{
	loff_t *spos = v;
	loff_t i = *spos, j;
	u64 n_packets = 0, n_bytes = 0;
	struct hfi1_ibdev *ibd = (struct hfi1_ibdev *)s->private;
	struct hfi1_devdata *dd = dd_from_dev(ibd);
	struct hfi1_ctxtdata *rcd;

	for (j = 0; j < dd->first_dyn_alloc_ctxt; j++) {
		rcd = hfi1_rcd_get_by_index(dd, j);
		if (rcd) {
			n_packets += rcd->opstats->stats[i].n_packets;
			n_bytes += rcd->opstats->stats[i].n_bytes;
		}
		hfi1_rcd_put(rcd);
	}
	return opcode_stats_show(s, i, n_packets, n_bytes);
}