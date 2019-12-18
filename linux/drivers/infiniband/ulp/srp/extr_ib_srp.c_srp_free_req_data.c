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
struct srp_target_port {int req_ring_size; int /*<<< orphan*/  indirect_size; TYPE_1__* srp_host; } ;
struct srp_request {struct srp_request* indirect_desc; scalar_t__ indirect_dma_addr; struct srp_request* map_page; struct srp_request* fmr_list; struct srp_request* fr_list; } ;
struct srp_rdma_ch {struct srp_request* req_ring; } ;
struct srp_device {scalar_t__ use_fast_reg; struct ib_device* dev; } ;
struct ib_device {int dummy; } ;
struct TYPE_2__ {struct srp_device* srp_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ib_dma_unmap_single (struct ib_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct srp_request*) ; 

__attribute__((used)) static void srp_free_req_data(struct srp_target_port *target,
			      struct srp_rdma_ch *ch)
{
	struct srp_device *dev = target->srp_host->srp_dev;
	struct ib_device *ibdev = dev->dev;
	struct srp_request *req;
	int i;

	if (!ch->req_ring)
		return;

	for (i = 0; i < target->req_ring_size; ++i) {
		req = &ch->req_ring[i];
		if (dev->use_fast_reg) {
			kfree(req->fr_list);
		} else {
			kfree(req->fmr_list);
			kfree(req->map_page);
		}
		if (req->indirect_dma_addr) {
			ib_dma_unmap_single(ibdev, req->indirect_dma_addr,
					    target->indirect_size,
					    DMA_TO_DEVICE);
		}
		kfree(req->indirect_desc);
	}

	kfree(ch->req_ring);
	ch->req_ring = NULL;
}