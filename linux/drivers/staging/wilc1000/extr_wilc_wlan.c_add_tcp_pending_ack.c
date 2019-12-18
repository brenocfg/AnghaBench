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
typedef  size_t u32 ;
struct tcp_ack_filter {size_t pending_base; size_t pending_acks_idx; TYPE_1__* pending_acks; } ;
struct wilc_vif {struct tcp_ack_filter ack_filter; } ;
struct txq_entry_t {size_t ack_idx; } ;
struct TYPE_2__ {size_t ack_num; size_t session_index; struct txq_entry_t* txqe; } ;

/* Variables and functions */
 size_t MAX_PENDING_ACKS ; 

__attribute__((used)) static inline void add_tcp_pending_ack(struct wilc_vif *vif, u32 ack,
				       u32 session_index,
				       struct txq_entry_t *txqe)
{
	struct tcp_ack_filter *f = &vif->ack_filter;
	u32 i = f->pending_base + f->pending_acks_idx;

	if (i < MAX_PENDING_ACKS) {
		f->pending_acks[i].ack_num = ack;
		f->pending_acks[i].txqe = txqe;
		f->pending_acks[i].session_index = session_index;
		txqe->ack_idx = i;
		f->pending_acks_idx++;
	}
}