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
struct iser_tx_desc {size_t wr_idx; TYPE_1__* wrs; } ;
struct ib_send_wr {struct ib_send_wr* next; } ;
struct TYPE_2__ {struct ib_send_wr send; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ib_send_wr *
iser_tx_next_wr(struct iser_tx_desc *tx_desc)
{
	struct ib_send_wr *cur_wr = &tx_desc->wrs[tx_desc->wr_idx].send;
	struct ib_send_wr *last_wr;

	if (tx_desc->wr_idx) {
		last_wr = &tx_desc->wrs[tx_desc->wr_idx - 1].send;
		last_wr->next = cur_wr;
	}
	tx_desc->wr_idx++;

	return cur_wr;
}