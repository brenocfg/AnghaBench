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
typedef  int /*<<< orphan*/  u32 ;
struct rvt_qp {int dummy; } ;
struct hfi1_pkt_state {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void update_tx_opstats(struct rvt_qp *qp, struct hfi1_pkt_state *ps,
			      u32 plen)
{
#ifdef CONFIG_DEBUG_FS
	struct hfi1_devdata *dd = dd_from_ibdev(qp->ibqp.device);
	struct hfi1_opcode_stats_perctx *s = get_cpu_ptr(dd->tx_opstats);

	inc_opstats(plen * 4, &s->stats[ps->opcode]);
	put_cpu_ptr(s);
#endif
}