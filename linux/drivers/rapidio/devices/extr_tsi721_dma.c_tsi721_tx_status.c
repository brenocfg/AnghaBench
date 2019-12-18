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
struct tsi721_bdma_chan {int /*<<< orphan*/  lock; } ;
struct dma_tx_state {int dummy; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
typedef  int /*<<< orphan*/  dma_cookie_t ;

/* Variables and functions */
 int dma_cookie_status (struct dma_chan*,int /*<<< orphan*/ ,struct dma_tx_state*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct tsi721_bdma_chan* to_tsi721_chan (struct dma_chan*) ; 

__attribute__((used)) static
enum dma_status tsi721_tx_status(struct dma_chan *dchan, dma_cookie_t cookie,
				 struct dma_tx_state *txstate)
{
	struct tsi721_bdma_chan *bdma_chan = to_tsi721_chan(dchan);
	enum dma_status	status;

	spin_lock_bh(&bdma_chan->lock);
	status = dma_cookie_status(dchan, cookie, txstate);
	spin_unlock_bh(&bdma_chan->lock);
	return status;
}