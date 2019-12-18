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
struct TYPE_2__ {int /*<<< orphan*/  dma_chan; int /*<<< orphan*/  markwq; } ;
struct scif_endpt {TYPE_1__ rma_info; } ;
typedef  scalar_t__ scif_epd_t ;
typedef  int dma_cookie_t ;

/* Variables and functions */
 scalar_t__ DMA_COMPLETE ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SCIF_NODE_ALIVE_TIMEOUT ; 
 int SCIF_REMOTE_FENCE ; 
 scalar_t__ dma_async_is_tx_complete (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _scif_fence_wait(scif_epd_t epd, int mark)
{
	struct scif_endpt *ep = (struct scif_endpt *)epd;
	dma_cookie_t cookie = mark & ~SCIF_REMOTE_FENCE;
	int err;

	/* Wait for DMA callback in scif_fence_mark_cb(..) */
	err = wait_event_interruptible_timeout(ep->rma_info.markwq,
					       dma_async_is_tx_complete(
					       ep->rma_info.dma_chan,
					       cookie, NULL, NULL) ==
					       DMA_COMPLETE,
					       SCIF_NODE_ALIVE_TIMEOUT);
	if (!err)
		err = -ETIMEDOUT;
	else if (err > 0)
		err = 0;
	return err;
}