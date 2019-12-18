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
typedef  scalar_t__ u32 ;
struct tg3_rx_prodring_set {scalar_t__ rx_std_prod_idx; scalar_t__ rx_jmb_prod_idx; } ;
struct tg3_napi {scalar_t__ tx_cons; scalar_t__* rx_rcb_prod_idx; scalar_t__ rx_rcb_ptr; struct tg3_rx_prodring_set prodring; TYPE_2__* hw_status; struct tg3* tp; } ;
struct tg3 {int rx_refill; int rxq_cnt; int /*<<< orphan*/  coal_now; struct tg3_napi* napi; } ;
struct TYPE_4__ {TYPE_1__* idx; } ;
struct TYPE_3__ {scalar_t__ tx_consumer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE_RSS ; 
 int /*<<< orphan*/  HOSTCC_MODE ; 
 int /*<<< orphan*/  TG3_RX_JMB_PROD_IDX_REG ; 
 int /*<<< orphan*/  TG3_RX_STD_PROD_IDX_REG ; 
 int /*<<< orphan*/  TX_RECOVERY_PENDING ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 scalar_t__ tg3_rx (struct tg3_napi*,int) ; 
 int tg3_rx_prodring_xfer (struct tg3*,struct tg3_rx_prodring_set*,struct tg3_rx_prodring_set*) ; 
 int /*<<< orphan*/  tg3_tx (struct tg3_napi*) ; 
 int /*<<< orphan*/  tw32_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32_rx_mbox (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ unlikely (scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int tg3_poll_work(struct tg3_napi *tnapi, int work_done, int budget)
{
	struct tg3 *tp = tnapi->tp;

	/* run TX completion thread */
	if (tnapi->hw_status->idx[0].tx_consumer != tnapi->tx_cons) {
		tg3_tx(tnapi);
		if (unlikely(tg3_flag(tp, TX_RECOVERY_PENDING)))
			return work_done;
	}

	if (!tnapi->rx_rcb_prod_idx)
		return work_done;

	/* run RX thread, within the bounds set by NAPI.
	 * All RX "locking" is done by ensuring outside
	 * code synchronizes with tg3->napi.poll()
	 */
	if (*(tnapi->rx_rcb_prod_idx) != tnapi->rx_rcb_ptr)
		work_done += tg3_rx(tnapi, budget - work_done);

	if (tg3_flag(tp, ENABLE_RSS) && tnapi == &tp->napi[1]) {
		struct tg3_rx_prodring_set *dpr = &tp->napi[0].prodring;
		int i, err = 0;
		u32 std_prod_idx = dpr->rx_std_prod_idx;
		u32 jmb_prod_idx = dpr->rx_jmb_prod_idx;

		tp->rx_refill = false;
		for (i = 1; i <= tp->rxq_cnt; i++)
			err |= tg3_rx_prodring_xfer(tp, dpr,
						    &tp->napi[i].prodring);

		wmb();

		if (std_prod_idx != dpr->rx_std_prod_idx)
			tw32_rx_mbox(TG3_RX_STD_PROD_IDX_REG,
				     dpr->rx_std_prod_idx);

		if (jmb_prod_idx != dpr->rx_jmb_prod_idx)
			tw32_rx_mbox(TG3_RX_JMB_PROD_IDX_REG,
				     dpr->rx_jmb_prod_idx);

		if (err)
			tw32_f(HOSTCC_MODE, tp->coal_now);
	}

	return work_done;
}