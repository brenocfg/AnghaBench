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
struct TYPE_2__ {int* va; } ;
struct wil_ring {int swtail; int swhead; int /*<<< orphan*/  hwtail; TYPE_1__ edma_rx_swtail; } ;
struct wil6210_priv {struct wil_ring ring_rx; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wil_dbg_txrx (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_err_ratelimited (struct wil6210_priv*,char*,int,int) ; 
 int wil_ring_alloc_skb_edma (struct wil6210_priv*,struct wil_ring*,int) ; 
 int wil_ring_next_head (struct wil_ring*) ; 
 int /*<<< orphan*/  wil_w (struct wil6210_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int wil_rx_refill_edma(struct wil6210_priv *wil)
{
	struct wil_ring *ring = &wil->ring_rx;
	u32 next_head;
	int rc = 0;
	ring->swtail = *ring->edma_rx_swtail.va;

	for (; next_head = wil_ring_next_head(ring),
	     (next_head != ring->swtail);
	     ring->swhead = next_head) {
		rc = wil_ring_alloc_skb_edma(wil, ring, ring->swhead);
		if (unlikely(rc)) {
			if (rc == -EAGAIN)
				wil_dbg_txrx(wil, "No free buffer ID found\n");
			else
				wil_err_ratelimited(wil,
						    "Error %d in refill desc[%d]\n",
						    rc, ring->swhead);
			break;
		}
	}

	/* make sure all writes to descriptors (shared memory) are done before
	 * committing them to HW
	 */
	wmb();

	wil_w(wil, ring->hwtail, ring->swhead);

	return rc;
}