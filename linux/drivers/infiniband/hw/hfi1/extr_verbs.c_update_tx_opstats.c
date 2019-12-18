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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct rvt_qp {TYPE_1__ ibqp; } ;
struct hfi1_pkt_state {size_t opcode; } ;
struct hfi1_opcode_stats_perctx {int /*<<< orphan*/ * stats; } ;
struct hfi1_devdata {int /*<<< orphan*/  tx_opstats; } ;

/* Variables and functions */
 struct hfi1_devdata* dd_from_ibdev (int /*<<< orphan*/ ) ; 
 struct hfi1_opcode_stats_perctx* get_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_opstats (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_cpu_ptr (struct hfi1_opcode_stats_perctx*) ; 

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