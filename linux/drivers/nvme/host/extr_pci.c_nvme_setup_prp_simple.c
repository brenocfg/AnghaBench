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
struct TYPE_4__ {void* prp2; void* prp1; } ;
struct nvme_rw_command {TYPE_2__ dptr; } ;
struct nvme_iod {unsigned int dma_len; scalar_t__ first_dma; } ;
struct TYPE_3__ {int page_size; } ;
struct nvme_dev {int /*<<< orphan*/  dev; TYPE_1__ ctrl; } ;
struct bio_vec {int bv_offset; unsigned int bv_len; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_RESOURCE ; 
 struct nvme_iod* blk_mq_rq_to_pdu (struct request*) ; 
 void* cpu_to_le64 (scalar_t__) ; 
 scalar_t__ dma_map_bvec (int /*<<< orphan*/ ,struct bio_vec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rq_dma_dir (struct request*) ; 

__attribute__((used)) static blk_status_t nvme_setup_prp_simple(struct nvme_dev *dev,
		struct request *req, struct nvme_rw_command *cmnd,
		struct bio_vec *bv)
{
	struct nvme_iod *iod = blk_mq_rq_to_pdu(req);
	unsigned int offset = bv->bv_offset & (dev->ctrl.page_size - 1);
	unsigned int first_prp_len = dev->ctrl.page_size - offset;

	iod->first_dma = dma_map_bvec(dev->dev, bv, rq_dma_dir(req), 0);
	if (dma_mapping_error(dev->dev, iod->first_dma))
		return BLK_STS_RESOURCE;
	iod->dma_len = bv->bv_len;

	cmnd->dptr.prp1 = cpu_to_le64(iod->first_dma);
	if (bv->bv_len > first_prp_len)
		cmnd->dptr.prp2 = cpu_to_le64(iod->first_dma + first_prp_len);
	return 0;
}