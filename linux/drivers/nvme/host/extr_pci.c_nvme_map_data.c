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
struct request {int /*<<< orphan*/  q; } ;
struct nvme_iod {scalar_t__ use_sgl; int /*<<< orphan*/  nents; int /*<<< orphan*/  sg; scalar_t__ dma_len; TYPE_1__* nvmeq; } ;
struct TYPE_4__ {int page_size; int sgls; } ;
struct nvme_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  iod_mempool; TYPE_2__ ctrl; } ;
struct nvme_command {int /*<<< orphan*/  rw; } ;
struct bio_vec {int bv_offset; int bv_len; int /*<<< orphan*/  bv_page; } ;
typedef  scalar_t__ blk_status_t ;
struct TYPE_3__ {scalar_t__ qid; } ;

/* Variables and functions */
 scalar_t__ BLK_STS_OK ; 
 scalar_t__ BLK_STS_RESOURCE ; 
 int /*<<< orphan*/  DMA_ATTR_NO_WARN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct nvme_iod* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  blk_rq_map_sg (int /*<<< orphan*/ ,struct request*,int /*<<< orphan*/ ) ; 
 int blk_rq_nr_phys_segments (struct request*) ; 
 int dma_map_sg_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_pci_p2pdma_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvme_pci_setup_prps (struct nvme_dev*,struct request*,int /*<<< orphan*/ *) ; 
 scalar_t__ nvme_pci_setup_sgls (struct nvme_dev*,struct request*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ nvme_pci_use_sgls (struct nvme_dev*,struct request*) ; 
 scalar_t__ nvme_setup_prp_simple (struct nvme_dev*,struct request*,int /*<<< orphan*/ *,struct bio_vec*) ; 
 scalar_t__ nvme_setup_sgl_simple (struct nvme_dev*,struct request*,int /*<<< orphan*/ *,struct bio_vec*) ; 
 int /*<<< orphan*/  nvme_unmap_data (struct nvme_dev*,struct request*) ; 
 int pci_p2pdma_map_sg_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bio_vec req_bvec (struct request*) ; 
 int /*<<< orphan*/  rq_dma_dir (struct request*) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static blk_status_t nvme_map_data(struct nvme_dev *dev, struct request *req,
		struct nvme_command *cmnd)
{
	struct nvme_iod *iod = blk_mq_rq_to_pdu(req);
	blk_status_t ret = BLK_STS_RESOURCE;
	int nr_mapped;

	if (blk_rq_nr_phys_segments(req) == 1) {
		struct bio_vec bv = req_bvec(req);

		if (!is_pci_p2pdma_page(bv.bv_page)) {
			if (bv.bv_offset + bv.bv_len <= dev->ctrl.page_size * 2)
				return nvme_setup_prp_simple(dev, req,
							     &cmnd->rw, &bv);

			if (iod->nvmeq->qid &&
			    dev->ctrl.sgls & ((1 << 0) | (1 << 1)))
				return nvme_setup_sgl_simple(dev, req,
							     &cmnd->rw, &bv);
		}
	}

	iod->dma_len = 0;
	iod->sg = mempool_alloc(dev->iod_mempool, GFP_ATOMIC);
	if (!iod->sg)
		return BLK_STS_RESOURCE;
	sg_init_table(iod->sg, blk_rq_nr_phys_segments(req));
	iod->nents = blk_rq_map_sg(req->q, req, iod->sg);
	if (!iod->nents)
		goto out;

	if (is_pci_p2pdma_page(sg_page(iod->sg)))
		nr_mapped = pci_p2pdma_map_sg_attrs(dev->dev, iod->sg,
				iod->nents, rq_dma_dir(req), DMA_ATTR_NO_WARN);
	else
		nr_mapped = dma_map_sg_attrs(dev->dev, iod->sg, iod->nents,
					     rq_dma_dir(req), DMA_ATTR_NO_WARN);
	if (!nr_mapped)
		goto out;

	iod->use_sgl = nvme_pci_use_sgls(dev, req);
	if (iod->use_sgl)
		ret = nvme_pci_setup_sgls(dev, req, &cmnd->rw, nr_mapped);
	else
		ret = nvme_pci_setup_prps(dev, req, &cmnd->rw);
out:
	if (ret != BLK_STS_OK)
		nvme_unmap_data(dev, req);
	return ret;
}