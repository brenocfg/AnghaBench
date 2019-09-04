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
struct srp_target_port {int req_ring_size; int /*<<< orphan*/  indirect_size; int /*<<< orphan*/  mr_per_cmd; TYPE_1__* srp_host; } ;
struct srp_request {int /*<<< orphan*/  indirect_dma_addr; int /*<<< orphan*/  indirect_desc; void* map_page; void* fmr_list; void* fr_list; } ;
struct srp_rdma_ch {struct srp_request* req_ring; struct srp_target_port* target; } ;
struct srp_device {int /*<<< orphan*/  max_pages_per_mr; scalar_t__ use_fast_reg; struct ib_device* dev; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {struct srp_device* srp_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ib_dma_map_single (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_dma_mapping_error (struct ib_device*,int /*<<< orphan*/ ) ; 
 struct srp_request* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* kmalloc_array (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int srp_alloc_req_data(struct srp_rdma_ch *ch)
{
	struct srp_target_port *target = ch->target;
	struct srp_device *srp_dev = target->srp_host->srp_dev;
	struct ib_device *ibdev = srp_dev->dev;
	struct srp_request *req;
	void *mr_list;
	dma_addr_t dma_addr;
	int i, ret = -ENOMEM;

	ch->req_ring = kcalloc(target->req_ring_size, sizeof(*ch->req_ring),
			       GFP_KERNEL);
	if (!ch->req_ring)
		goto out;

	for (i = 0; i < target->req_ring_size; ++i) {
		req = &ch->req_ring[i];
		mr_list = kmalloc_array(target->mr_per_cmd, sizeof(void *),
					GFP_KERNEL);
		if (!mr_list)
			goto out;
		if (srp_dev->use_fast_reg) {
			req->fr_list = mr_list;
		} else {
			req->fmr_list = mr_list;
			req->map_page = kmalloc_array(srp_dev->max_pages_per_mr,
						      sizeof(void *),
						      GFP_KERNEL);
			if (!req->map_page)
				goto out;
		}
		req->indirect_desc = kmalloc(target->indirect_size, GFP_KERNEL);
		if (!req->indirect_desc)
			goto out;

		dma_addr = ib_dma_map_single(ibdev, req->indirect_desc,
					     target->indirect_size,
					     DMA_TO_DEVICE);
		if (ib_dma_mapping_error(ibdev, dma_addr))
			goto out;

		req->indirect_dma_addr = dma_addr;
	}
	ret = 0;

out:
	return ret;
}