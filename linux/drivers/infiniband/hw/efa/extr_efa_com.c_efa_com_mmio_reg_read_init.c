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
struct efa_com_mmio_read {int /*<<< orphan*/  mmio_read_timeout; scalar_t__ seq_num; TYPE_1__* read_resp; int /*<<< orphan*/  read_resp_dma_addr; int /*<<< orphan*/  lock; } ;
struct efa_com_dev {int /*<<< orphan*/  dmadev; struct efa_com_mmio_read mmio_read; } ;
struct TYPE_2__ {scalar_t__ req_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFA_REG_READ_TIMEOUT_US ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efa_com_mmio_reg_read_resp_addr_init (struct efa_com_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int efa_com_mmio_reg_read_init(struct efa_com_dev *edev)
{
	struct efa_com_mmio_read *mmio_read = &edev->mmio_read;

	spin_lock_init(&mmio_read->lock);
	mmio_read->read_resp =
		dma_alloc_coherent(edev->dmadev, sizeof(*mmio_read->read_resp),
				   &mmio_read->read_resp_dma_addr, GFP_KERNEL);
	if (!mmio_read->read_resp)
		return -ENOMEM;

	efa_com_mmio_reg_read_resp_addr_init(edev);

	mmio_read->read_resp->req_id = 0;
	mmio_read->seq_num = 0;
	mmio_read->mmio_read_timeout = EFA_REG_READ_TIMEOUT_US;

	return 0;
}