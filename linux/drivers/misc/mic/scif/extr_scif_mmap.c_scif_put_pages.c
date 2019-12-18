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
struct scifmsg {int /*<<< orphan*/ * payload; int /*<<< orphan*/  src; int /*<<< orphan*/  uop; } ;
struct scif_window {scalar_t__ magic; int /*<<< orphan*/  peer_window; int /*<<< orphan*/  list; int /*<<< orphan*/  ref_count; scalar_t__ ep; } ;
struct scif_range {int nr_pages; int /*<<< orphan*/  va; int /*<<< orphan*/  phys_addr; struct scif_window* cookie; } ;
struct TYPE_3__ {int /*<<< orphan*/  rma_lock; int /*<<< orphan*/  dma_chan; } ;
struct scif_endpt {scalar_t__ state; TYPE_1__ rma_info; TYPE_2__* remote_dev; int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  sdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCONN ; 
 scalar_t__ SCIFEP_CONNECTED ; 
 scalar_t__ SCIFEP_DISCONNECTED ; 
 scalar_t__ SCIFEP_MAGIC ; 
 int /*<<< orphan*/  SCIF_MUNMAP ; 
 int /*<<< orphan*/  kfree (struct scif_range*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_destroy_remote_window (struct scif_window*) ; 
 int /*<<< orphan*/  scif_drain_dma_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_free (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scif_nodeqp_send (TYPE_2__*,struct scifmsg*) ; 
 int /*<<< orphan*/  scif_put_window (struct scif_window*,int) ; 

int scif_put_pages(struct scif_range *pages)
{
	struct scif_endpt *ep;
	struct scif_window *window;
	struct scifmsg msg;

	if (!pages || !pages->cookie)
		return -EINVAL;

	window = pages->cookie;

	if (!window || window->magic != SCIFEP_MAGIC)
		return -EINVAL;

	ep = (struct scif_endpt *)window->ep;
	/*
	 * If the state is SCIFEP_CONNECTED or SCIFEP_DISCONNECTED then the
	 * callee should be allowed to release references to the pages,
	 * else the endpoint was not connected in the first place,
	 * hence the ENOTCONN.
	 */
	if (ep->state != SCIFEP_CONNECTED && ep->state != SCIFEP_DISCONNECTED)
		return -ENOTCONN;

	mutex_lock(&ep->rma_info.rma_lock);

	scif_put_window(window, pages->nr_pages);

	/* Initiate window destruction if ref count is zero */
	if (!window->ref_count) {
		list_del(&window->list);
		mutex_unlock(&ep->rma_info.rma_lock);
		scif_drain_dma_intr(ep->remote_dev->sdev,
				    ep->rma_info.dma_chan);
		/* Inform the peer about this window being destroyed. */
		msg.uop = SCIF_MUNMAP;
		msg.src = ep->port;
		msg.payload[0] = window->peer_window;
		/* No error handling for notification messages */
		scif_nodeqp_send(ep->remote_dev, &msg);
		/* Destroy this window from the peer's registered AS */
		scif_destroy_remote_window(window);
	} else {
		mutex_unlock(&ep->rma_info.rma_lock);
	}

	scif_free(pages->phys_addr, pages->nr_pages * sizeof(dma_addr_t));
	scif_free(pages->va, pages->nr_pages * sizeof(void *));
	kfree(pages);
	return 0;
}