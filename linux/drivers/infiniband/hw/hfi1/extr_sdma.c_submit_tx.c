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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u16 ;
struct sdma_txreq {int num_desc; size_t next_descq_idx; scalar_t__ sn; struct sdma_desc* descp; } ;
struct sdma_engine {size_t descq_tail; size_t sdma_mask; size_t tx_tail; int desc_avail; struct sdma_txreq** tx_ring; int /*<<< orphan*/  tail_sn; TYPE_1__* descq; } ;
struct sdma_desc {int /*<<< orphan*/ * qw; } ;
struct TYPE_2__ {void** qw; } ;

/* Variables and functions */
 int SDMA_AHG_APPLY_UPDATE1 ; 
 int /*<<< orphan*/  WARN_ON_ONCE (struct sdma_txreq*) ; 
 int /*<<< orphan*/  add_gen (struct sdma_engine*,int /*<<< orphan*/ ) ; 
 int ahg_mode (struct sdma_txreq*) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_hfi1_sdma_descriptor (struct sdma_engine*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,TYPE_1__*) ; 
 int /*<<< orphan*/  trace_hfi1_sdma_in_sn (struct sdma_engine*,scalar_t__) ; 

__attribute__((used)) static inline u16 submit_tx(struct sdma_engine *sde, struct sdma_txreq *tx)
{
	int i;
	u16 tail;
	struct sdma_desc *descp = tx->descp;
	u8 skip = 0, mode = ahg_mode(tx);

	tail = sde->descq_tail & sde->sdma_mask;
	sde->descq[tail].qw[0] = cpu_to_le64(descp->qw[0]);
	sde->descq[tail].qw[1] = cpu_to_le64(add_gen(sde, descp->qw[1]));
	trace_hfi1_sdma_descriptor(sde, descp->qw[0], descp->qw[1],
				   tail, &sde->descq[tail]);
	tail = ++sde->descq_tail & sde->sdma_mask;
	descp++;
	if (mode > SDMA_AHG_APPLY_UPDATE1)
		skip = mode >> 1;
	for (i = 1; i < tx->num_desc; i++, descp++) {
		u64 qw1;

		sde->descq[tail].qw[0] = cpu_to_le64(descp->qw[0]);
		if (skip) {
			/* edits don't have generation */
			qw1 = descp->qw[1];
			skip--;
		} else {
			/* replace generation with real one for non-edits */
			qw1 = add_gen(sde, descp->qw[1]);
		}
		sde->descq[tail].qw[1] = cpu_to_le64(qw1);
		trace_hfi1_sdma_descriptor(sde, descp->qw[0], qw1,
					   tail, &sde->descq[tail]);
		tail = ++sde->descq_tail & sde->sdma_mask;
	}
	tx->next_descq_idx = tail;
#ifdef CONFIG_HFI1_DEBUG_SDMA_ORDER
	tx->sn = sde->tail_sn++;
	trace_hfi1_sdma_in_sn(sde, tx->sn);
	WARN_ON_ONCE(sde->tx_ring[sde->tx_tail & sde->sdma_mask]);
#endif
	sde->tx_ring[sde->tx_tail++ & sde->sdma_mask] = tx;
	sde->desc_avail -= tx->num_desc;
	return tail;
}