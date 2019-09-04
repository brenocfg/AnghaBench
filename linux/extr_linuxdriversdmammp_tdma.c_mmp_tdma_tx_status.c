#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mmp_tdma_chan {int status; scalar_t__ pos; scalar_t__ buf_len; } ;
struct dma_tx_state {int dummy; } ;
struct dma_chan {int /*<<< orphan*/  cookie; int /*<<< orphan*/  completed_cookie; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
typedef  int /*<<< orphan*/  dma_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  dma_set_tx_state (struct dma_tx_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mmp_tdma_get_pos (struct mmp_tdma_chan*) ; 
 struct mmp_tdma_chan* to_mmp_tdma_chan (struct dma_chan*) ; 

__attribute__((used)) static enum dma_status mmp_tdma_tx_status(struct dma_chan *chan,
			dma_cookie_t cookie, struct dma_tx_state *txstate)
{
	struct mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);

	tdmac->pos = mmp_tdma_get_pos(tdmac);
	dma_set_tx_state(txstate, chan->completed_cookie, chan->cookie,
			 tdmac->buf_len - tdmac->pos);

	return tdmac->status;
}