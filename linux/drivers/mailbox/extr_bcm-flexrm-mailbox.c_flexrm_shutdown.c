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
typedef  size_t u32 ;
struct mbox_chan {struct flexrm_ring* con_priv; } ;
struct flexrm_ring {int irq_requested; int /*<<< orphan*/ * bd_base; int /*<<< orphan*/  bd_dma_base; TYPE_1__* mbox; int /*<<< orphan*/ * cmpl_base; int /*<<< orphan*/  cmpl_dma_base; int /*<<< orphan*/  irq; int /*<<< orphan*/  requests_bmap; struct brcm_message** requests; int /*<<< orphan*/  num; scalar_t__ regs; } ;
struct brcm_message {int /*<<< orphan*/  error; } ;
struct TYPE_2__ {int /*<<< orphan*/  bd_pool; int /*<<< orphan*/  cmpl_pool; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONTROL_FLUSH_SHIFT ; 
 int /*<<< orphan*/  EIO ; 
 int FLUSH_DONE_MASK ; 
 scalar_t__ RING_CONTROL ; 
 scalar_t__ RING_FLUSH_DONE ; 
 size_t RING_MAX_REQ_COUNT ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flexrm_dma_unmap (int /*<<< orphan*/ ,struct brcm_message*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct flexrm_ring*) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbox_chan_received_data (struct mbox_chan*,struct brcm_message*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void flexrm_shutdown(struct mbox_chan *chan)
{
	u32 reqid;
	unsigned int timeout;
	struct brcm_message *msg;
	struct flexrm_ring *ring = chan->con_priv;

	/* Disable/inactivate ring */
	writel_relaxed(0x0, ring->regs + RING_CONTROL);

	/* Set ring flush state */
	timeout = 1000; /* timeout of 1s */
	writel_relaxed(BIT(CONTROL_FLUSH_SHIFT),
			ring->regs + RING_CONTROL);
	do {
		if (readl_relaxed(ring->regs + RING_FLUSH_DONE) &
		    FLUSH_DONE_MASK)
			break;
		mdelay(1);
	} while (--timeout);
	if (!timeout)
		dev_err(ring->mbox->dev,
			"setting ring%d flush state timedout\n", ring->num);

	/* Clear ring flush state */
	timeout = 1000; /* timeout of 1s */
	writel_relaxed(0x0, ring->regs + RING_CONTROL);
	do {
		if (!(readl_relaxed(ring->regs + RING_FLUSH_DONE) &
		      FLUSH_DONE_MASK))
			break;
		mdelay(1);
	} while (--timeout);
	if (!timeout)
		dev_err(ring->mbox->dev,
			"clearing ring%d flush state timedout\n", ring->num);

	/* Abort all in-flight requests */
	for (reqid = 0; reqid < RING_MAX_REQ_COUNT; reqid++) {
		msg = ring->requests[reqid];
		if (!msg)
			continue;

		/* Release reqid for recycling */
		ring->requests[reqid] = NULL;

		/* Unmap DMA mappings */
		flexrm_dma_unmap(ring->mbox->dev, msg);

		/* Give-back message to mailbox client */
		msg->error = -EIO;
		mbox_chan_received_data(chan, msg);
	}

	/* Clear requests bitmap */
	bitmap_zero(ring->requests_bmap, RING_MAX_REQ_COUNT);

	/* Release IRQ */
	if (ring->irq_requested) {
		irq_set_affinity_hint(ring->irq, NULL);
		free_irq(ring->irq, ring);
		ring->irq_requested = false;
	}

	/* Free-up completion descriptor ring */
	if (ring->cmpl_base) {
		dma_pool_free(ring->mbox->cmpl_pool,
			      ring->cmpl_base, ring->cmpl_dma_base);
		ring->cmpl_base = NULL;
	}

	/* Free-up BD descriptor ring */
	if (ring->bd_base) {
		dma_pool_free(ring->mbox->bd_pool,
			      ring->bd_base, ring->bd_dma_base);
		ring->bd_base = NULL;
	}
}