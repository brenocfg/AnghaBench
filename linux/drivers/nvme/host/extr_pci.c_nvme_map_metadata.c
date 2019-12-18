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
struct request {int dummy; } ;
struct nvme_iod {int /*<<< orphan*/  meta_dma; } ;
struct nvme_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  metadata; } ;
struct nvme_command {TYPE_1__ rw; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 struct nvme_iod* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_bvec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_dma_dir (struct request*) ; 
 int /*<<< orphan*/  rq_integrity_vec (struct request*) ; 

__attribute__((used)) static blk_status_t nvme_map_metadata(struct nvme_dev *dev, struct request *req,
		struct nvme_command *cmnd)
{
	struct nvme_iod *iod = blk_mq_rq_to_pdu(req);

	iod->meta_dma = dma_map_bvec(dev->dev, rq_integrity_vec(req),
			rq_dma_dir(req), 0);
	if (dma_mapping_error(dev->dev, iod->meta_dma))
		return BLK_STS_IOERR;
	cmnd->rw.metadata = cpu_to_le64(iod->meta_dma);
	return 0;
}