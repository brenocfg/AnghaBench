#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ map_bufs_cnt; int /*<<< orphan*/ * buf; struct nitrox_sglist* sglist; struct nitrox_sglist* sgcomp; int /*<<< orphan*/  len; int /*<<< orphan*/  dma; int /*<<< orphan*/  dir; } ;
struct TYPE_5__ {int /*<<< orphan*/  completion_dma; int /*<<< orphan*/  orh_dma; } ;
struct TYPE_4__ {scalar_t__ map_bufs_cnt; int /*<<< orphan*/ * buf; struct nitrox_sglist* sglist; struct nitrox_sglist* sgcomp; int /*<<< orphan*/  len; int /*<<< orphan*/  dma; int /*<<< orphan*/  dir; } ;
struct nitrox_softreq {TYPE_3__ out; TYPE_2__ resp; int /*<<< orphan*/  inplace; TYPE_1__ in; struct nitrox_device* ndev; } ;
struct nitrox_sglist {int /*<<< orphan*/  len; int /*<<< orphan*/  dma; } ;
struct nitrox_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_HLEN ; 
 struct device* DEV (struct nitrox_device*) ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ORH_HLEN ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nitrox_sglist*) ; 

__attribute__((used)) static void softreq_unmap_sgbufs(struct nitrox_softreq *sr)
{
	struct nitrox_device *ndev = sr->ndev;
	struct device *dev = DEV(ndev);
	struct nitrox_sglist *sglist;

	/* unmap in sgbuf */
	sglist = sr->in.sglist;
	if (!sglist)
		goto out_unmap;

	/* unmap iv */
	dma_unmap_single(dev, sglist->dma, sglist->len, DMA_BIDIRECTIONAL);
	/* unmpa src sglist */
	dma_unmap_sg(dev, sr->in.buf, (sr->in.map_bufs_cnt - 1), sr->in.dir);
	/* unamp gather component */
	dma_unmap_single(dev, sr->in.dma, sr->in.len, DMA_TO_DEVICE);
	kfree(sr->in.sglist);
	kfree(sr->in.sgcomp);
	sr->in.sglist = NULL;
	sr->in.buf = NULL;
	sr->in.map_bufs_cnt = 0;

out_unmap:
	/* unmap out sgbuf */
	sglist = sr->out.sglist;
	if (!sglist)
		return;

	/* unmap orh */
	dma_unmap_single(dev, sr->resp.orh_dma, ORH_HLEN, sr->out.dir);

	/* unmap dst sglist */
	if (!sr->inplace) {
		dma_unmap_sg(dev, sr->out.buf, (sr->out.map_bufs_cnt - 3),
			     sr->out.dir);
	}
	/* unmap completion */
	dma_unmap_single(dev, sr->resp.completion_dma, COMP_HLEN, sr->out.dir);

	/* unmap scatter component */
	dma_unmap_single(dev, sr->out.dma, sr->out.len, DMA_TO_DEVICE);
	kfree(sr->out.sglist);
	kfree(sr->out.sgcomp);
	sr->out.sglist = NULL;
	sr->out.buf = NULL;
	sr->out.map_bufs_cnt = 0;
}