#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nitrox_softreq {int /*<<< orphan*/  gfp; struct nitrox_device* ndev; } ;
struct nitrox_sgtable {int nr_sgcomp; size_t len; int /*<<< orphan*/  dma; struct nitrox_sgcomp* sgcomp; struct nitrox_sglist* sglist; } ;
struct nitrox_sglist {int /*<<< orphan*/  dma; int /*<<< orphan*/  len; } ;
struct nitrox_sgcomp {int /*<<< orphan*/ * dma; int /*<<< orphan*/ * len; } ;
struct nitrox_device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEV (struct nitrox_device*) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,struct nitrox_sgcomp*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nitrox_sgcomp*) ; 
 struct nitrox_sgcomp* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int roundup (int,int) ; 

__attribute__((used)) static int create_sg_component(struct nitrox_softreq *sr,
			       struct nitrox_sgtable *sgtbl, int map_nents)
{
	struct nitrox_device *ndev = sr->ndev;
	struct nitrox_sgcomp *sgcomp;
	struct nitrox_sglist *sglist;
	dma_addr_t dma;
	size_t sz_comp;
	int i, j, nr_sgcomp;

	nr_sgcomp = roundup(map_nents, 4) / 4;

	/* each component holds 4 dma pointers */
	sz_comp = nr_sgcomp * sizeof(*sgcomp);
	sgcomp = kzalloc(sz_comp, sr->gfp);
	if (!sgcomp)
		return -ENOMEM;

	sgtbl->sgcomp = sgcomp;
	sgtbl->nr_sgcomp = nr_sgcomp;

	sglist = sgtbl->sglist;
	/* populate device sg component */
	for (i = 0; i < nr_sgcomp; i++) {
		for (j = 0; j < 4; j++) {
			sgcomp->len[j] = cpu_to_be16(sglist->len);
			sgcomp->dma[j] = cpu_to_be64(sglist->dma);
			sglist++;
		}
		sgcomp++;
	}
	/* map the device sg component */
	dma = dma_map_single(DEV(ndev), sgtbl->sgcomp, sz_comp, DMA_TO_DEVICE);
	if (dma_mapping_error(DEV(ndev), dma)) {
		kfree(sgtbl->sgcomp);
		sgtbl->sgcomp = NULL;
		return -ENOMEM;
	}

	sgtbl->dma = dma;
	sgtbl->len = sz_comp;

	return 0;
}