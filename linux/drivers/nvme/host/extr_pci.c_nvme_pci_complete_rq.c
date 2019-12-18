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
struct request {int dummy; } ;
struct nvme_iod {int /*<<< orphan*/  meta_dma; TYPE_1__* nvmeq; } ;
struct nvme_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  bv_len; } ;
struct TYPE_3__ {struct nvme_dev* dev; } ;

/* Variables and functions */
 scalar_t__ blk_integrity_rq (struct request*) ; 
 struct nvme_iod* blk_mq_rq_to_pdu (struct request*) ; 
 scalar_t__ blk_rq_nr_phys_segments (struct request*) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_cleanup_cmd (struct request*) ; 
 int /*<<< orphan*/  nvme_complete_rq (struct request*) ; 
 int /*<<< orphan*/  nvme_unmap_data (struct nvme_dev*,struct request*) ; 
 int /*<<< orphan*/  rq_data_dir (struct request*) ; 
 TYPE_2__* rq_integrity_vec (struct request*) ; 

__attribute__((used)) static void nvme_pci_complete_rq(struct request *req)
{
	struct nvme_iod *iod = blk_mq_rq_to_pdu(req);
	struct nvme_dev *dev = iod->nvmeq->dev;

	nvme_cleanup_cmd(req);
	if (blk_integrity_rq(req))
		dma_unmap_page(dev->dev, iod->meta_dma,
			       rq_integrity_vec(req)->bv_len, rq_data_dir(req));
	if (blk_rq_nr_phys_segments(req))
		nvme_unmap_data(dev, req);
	nvme_complete_rq(req);
}