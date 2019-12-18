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
struct mei_msg_hdr {int dummy; } ;
struct mei_device {int /*<<< orphan*/  init_clients_timer; int /*<<< orphan*/  hbm_state; int /*<<< orphan*/  dev; TYPE_2__* dr_dscr; } ;
struct hbm_dma_setup_request {TYPE_1__* dma_dscr; int /*<<< orphan*/  hbm_cmd; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  size; int /*<<< orphan*/  daddr; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  addr_lo; int /*<<< orphan*/  addr_hi; } ;

/* Variables and functions */
 unsigned int DMA_DSCR_NUM ; 
 int /*<<< orphan*/  MEI_CLIENTS_INIT_TIMEOUT ; 
 int /*<<< orphan*/  MEI_HBM_DMA_SETUP_REQ_CMD ; 
 int /*<<< orphan*/  MEI_HBM_DR_SETUP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_dma_ring_reset (struct mei_device*) ; 
 int /*<<< orphan*/  mei_hbm_hdr (struct mei_msg_hdr*,size_t const) ; 
 int mei_hbm_write_message (struct mei_device*,struct mei_msg_hdr*,struct hbm_dma_setup_request*) ; 
 int /*<<< orphan*/  mei_schedule_stall_timer (struct mei_device*) ; 
 int /*<<< orphan*/  memset (struct hbm_dma_setup_request*,int /*<<< orphan*/ ,size_t const) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mei_hbm_dma_setup_req(struct mei_device *dev)
{
	struct mei_msg_hdr mei_hdr;
	struct hbm_dma_setup_request req;
	const size_t len = sizeof(struct hbm_dma_setup_request);
	unsigned int i;
	int ret;

	mei_hbm_hdr(&mei_hdr, len);

	memset(&req, 0, len);
	req.hbm_cmd = MEI_HBM_DMA_SETUP_REQ_CMD;
	for (i = 0; i < DMA_DSCR_NUM; i++) {
		phys_addr_t paddr;

		paddr = dev->dr_dscr[i].daddr;
		req.dma_dscr[i].addr_hi = upper_32_bits(paddr);
		req.dma_dscr[i].addr_lo = lower_32_bits(paddr);
		req.dma_dscr[i].size = dev->dr_dscr[i].size;
	}

	mei_dma_ring_reset(dev);

	ret = mei_hbm_write_message(dev, &mei_hdr, &req);
	if (ret) {
		dev_err(dev->dev, "dma setup request write failed: ret = %d.\n",
			ret);
		return ret;
	}

	dev->hbm_state = MEI_HBM_DR_SETUP;
	dev->init_clients_timer = MEI_CLIENTS_INIT_TIMEOUT;
	mei_schedule_stall_timer(dev);
	return 0;
}