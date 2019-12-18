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
struct cpsw_vector {int budget; int /*<<< orphan*/  ch; } ;
struct cpsw_common {int tx_ch_num; int speed; int rx_ch_num; TYPE_1__* rxv; struct cpsw_vector* txv; } ;
struct TYPE_2__ {int budget; } ;

/* Variables and functions */
 int CPSW_POLL_WEIGHT ; 
 int cpdma_chan_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpdma_chan_set_weight (int /*<<< orphan*/ ,int) ; 

void cpsw_split_res(struct cpsw_common *cpsw)
{
	u32 consumed_rate = 0, bigest_rate = 0;
	struct cpsw_vector *txv = cpsw->txv;
	int i, ch_weight, rlim_ch_num = 0;
	int budget, bigest_rate_ch = 0;
	u32 ch_rate, max_rate;
	int ch_budget = 0;

	for (i = 0; i < cpsw->tx_ch_num; i++) {
		ch_rate = cpdma_chan_get_rate(txv[i].ch);
		if (!ch_rate)
			continue;

		rlim_ch_num++;
		consumed_rate += ch_rate;
	}

	if (cpsw->tx_ch_num == rlim_ch_num) {
		max_rate = consumed_rate;
	} else if (!rlim_ch_num) {
		ch_budget = CPSW_POLL_WEIGHT / cpsw->tx_ch_num;
		bigest_rate = 0;
		max_rate = consumed_rate;
	} else {
		max_rate = cpsw->speed * 1000;

		/* if max_rate is less then expected due to reduced link speed,
		 * split proportionally according next potential max speed
		 */
		if (max_rate < consumed_rate)
			max_rate *= 10;

		if (max_rate < consumed_rate)
			max_rate *= 10;

		ch_budget = (consumed_rate * CPSW_POLL_WEIGHT) / max_rate;
		ch_budget = (CPSW_POLL_WEIGHT - ch_budget) /
			    (cpsw->tx_ch_num - rlim_ch_num);
		bigest_rate = (max_rate - consumed_rate) /
			      (cpsw->tx_ch_num - rlim_ch_num);
	}

	/* split tx weight/budget */
	budget = CPSW_POLL_WEIGHT;
	for (i = 0; i < cpsw->tx_ch_num; i++) {
		ch_rate = cpdma_chan_get_rate(txv[i].ch);
		if (ch_rate) {
			txv[i].budget = (ch_rate * CPSW_POLL_WEIGHT) / max_rate;
			if (!txv[i].budget)
				txv[i].budget++;
			if (ch_rate > bigest_rate) {
				bigest_rate_ch = i;
				bigest_rate = ch_rate;
			}

			ch_weight = (ch_rate * 100) / max_rate;
			if (!ch_weight)
				ch_weight++;
			cpdma_chan_set_weight(cpsw->txv[i].ch, ch_weight);
		} else {
			txv[i].budget = ch_budget;
			if (!bigest_rate_ch)
				bigest_rate_ch = i;
			cpdma_chan_set_weight(cpsw->txv[i].ch, 0);
		}

		budget -= txv[i].budget;
	}

	if (budget)
		txv[bigest_rate_ch].budget += budget;

	/* split rx budget */
	budget = CPSW_POLL_WEIGHT;
	ch_budget = budget / cpsw->rx_ch_num;
	for (i = 0; i < cpsw->rx_ch_num; i++) {
		cpsw->rxv[i].budget = ch_budget;
		budget -= ch_budget;
	}

	if (budget)
		cpsw->rxv[0].budget += budget;
}