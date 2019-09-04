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
struct TYPE_2__ {int dsize_log2; int ring_size; scalar_t__ cur; } ;
struct fec_enet_priv_tx_q {TYPE_1__ bd; scalar_t__ dirty_tx; } ;

/* Variables and functions */

__attribute__((used)) static int fec_enet_get_free_txdesc_num(struct fec_enet_priv_tx_q *txq)
{
	int entries;

	entries = (((const char *)txq->dirty_tx -
			(const char *)txq->bd.cur) >> txq->bd.dsize_log2) - 1;

	return entries >= 0 ? entries : entries + txq->bd.ring_size;
}