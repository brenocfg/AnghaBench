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
struct ena_com_mmio_read {int seq_num; int readless_supported; TYPE_1__* read_resp; int /*<<< orphan*/  read_resp_dma_addr; int /*<<< orphan*/  lock; } ;
struct ena_com_dev {int /*<<< orphan*/  dmadev; struct ena_com_mmio_read mmio_read; } ;
struct TYPE_2__ {int req_id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_com_mmio_reg_read_request_write_dev_addr (struct ena_com_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int ena_com_mmio_reg_read_request_init(struct ena_com_dev *ena_dev)
{
	struct ena_com_mmio_read *mmio_read = &ena_dev->mmio_read;

	spin_lock_init(&mmio_read->lock);
	mmio_read->read_resp =
		dma_alloc_coherent(ena_dev->dmadev,
				   sizeof(*mmio_read->read_resp),
				   &mmio_read->read_resp_dma_addr, GFP_KERNEL);
	if (unlikely(!mmio_read->read_resp))
		goto err;

	ena_com_mmio_reg_read_request_write_dev_addr(ena_dev);

	mmio_read->read_resp->req_id = 0x0;
	mmio_read->seq_num = 0x0;
	mmio_read->readless_supported = true;

	return 0;

err:

	return -ENOMEM;
}