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
struct TYPE_2__ {int /*<<< orphan*/  last_produce_idx; } ;
struct emac_tx_queue {TYPE_1__ tpd; } ;
struct emac_adapter {int /*<<< orphan*/  tpd_size; } ;

/* Variables and functions */
 int /*<<< orphan*/ * EMAC_TPD (struct emac_tx_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMAC_TPD_LAST_FRAGMENT ; 

__attribute__((used)) static void emac_tx_tpd_mark_last(struct emac_adapter *adpt,
				  struct emac_tx_queue *tx_q)
{
	u32 *hw_tpd =
		EMAC_TPD(tx_q, adpt->tpd_size, tx_q->tpd.last_produce_idx);
	u32 tmp_tpd;

	tmp_tpd = *(hw_tpd + 1);
	tmp_tpd |= EMAC_TPD_LAST_FRAGMENT;
	*(hw_tpd + 1) = tmp_tpd;
}