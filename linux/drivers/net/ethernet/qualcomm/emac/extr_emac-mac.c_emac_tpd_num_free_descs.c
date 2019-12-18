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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ produce_idx; scalar_t__ consume_idx; scalar_t__ count; } ;
struct emac_tx_queue {TYPE_1__ tpd; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int emac_tpd_num_free_descs(struct emac_tx_queue *tx_q)
{
	u32 produce_idx = tx_q->tpd.produce_idx;
	u32 consume_idx = tx_q->tpd.consume_idx;

	return (consume_idx > produce_idx) ?
		(consume_idx - produce_idx - 1) :
		(tx_q->tpd.count + consume_idx - produce_idx - 1);
}