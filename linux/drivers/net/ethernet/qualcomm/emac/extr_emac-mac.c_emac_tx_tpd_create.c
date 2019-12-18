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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ last_produce_idx; scalar_t__ produce_idx; scalar_t__ count; } ;
struct emac_tx_queue {TYPE_1__ tpd; } ;
struct emac_tpd {int /*<<< orphan*/ * word; } ;
struct emac_adapter {int /*<<< orphan*/  tpd_size; } ;

/* Variables and functions */
 int /*<<< orphan*/ * EMAC_TPD (struct emac_tx_queue*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void emac_tx_tpd_create(struct emac_adapter *adpt,
			       struct emac_tx_queue *tx_q, struct emac_tpd *tpd)
{
	u32 *hw_tpd;

	tx_q->tpd.last_produce_idx = tx_q->tpd.produce_idx;
	hw_tpd = EMAC_TPD(tx_q, adpt->tpd_size, tx_q->tpd.produce_idx);

	if (++tx_q->tpd.produce_idx == tx_q->tpd.count)
		tx_q->tpd.produce_idx = 0;

	*(hw_tpd++) = tpd->word[0];
	*(hw_tpd++) = tpd->word[1];
	*(hw_tpd++) = tpd->word[2];
	*hw_tpd = tpd->word[3];
}