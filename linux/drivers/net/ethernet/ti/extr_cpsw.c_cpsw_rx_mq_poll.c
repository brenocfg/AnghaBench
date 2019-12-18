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
struct napi_struct {int dummy; } ;
struct cpsw_vector {int budget; int /*<<< orphan*/  ch; } ;
struct cpsw_common {TYPE_1__* wr_regs; struct cpsw_vector* rxv; int /*<<< orphan*/  dma; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_en; } ;

/* Variables and functions */
 scalar_t__ cpdma_chan_process (int /*<<< orphan*/ ,int) ; 
 int cpdma_ctrl_rxchs_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_complete_done (struct napi_struct*,int) ; 
 struct cpsw_common* napi_to_cpsw (struct napi_struct*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cpsw_rx_mq_poll(struct napi_struct *napi_rx, int budget)
{
	u32			ch_map;
	int			num_rx, cur_budget, ch;
	struct cpsw_common	*cpsw = napi_to_cpsw(napi_rx);
	struct cpsw_vector	*rxv;

	/* process every unprocessed channel */
	ch_map = cpdma_ctrl_rxchs_state(cpsw->dma);
	for (ch = 0, num_rx = 0; ch_map; ch_map >>= 1, ch++) {
		if (!(ch_map & 0x01))
			continue;

		rxv = &cpsw->rxv[ch];
		if (unlikely(rxv->budget > budget - num_rx))
			cur_budget = budget - num_rx;
		else
			cur_budget = rxv->budget;

		num_rx += cpdma_chan_process(rxv->ch, cur_budget);
		if (num_rx >= budget)
			break;
	}

	if (num_rx < budget) {
		napi_complete_done(napi_rx, num_rx);
		writel(0xff, &cpsw->wr_regs->rx_en);
	}

	return num_rx;
}