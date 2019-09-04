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
typedef  size_t u32 ;
struct hfi1_devdata {TYPE_1__* pcidev; } ;
struct TYPE_5__ {size_t alloced; TYPE_3__* buffers; TYPE_3__* rcvtids; } ;
struct hfi1_ctxtdata {void* rcvhdrq; TYPE_3__* opstats; int /*<<< orphan*/ * subctxt_rcvhdr_base; int /*<<< orphan*/ * subctxt_rcvegrbuf; int /*<<< orphan*/ * subctxt_uregbase; int /*<<< orphan*/ * sc; TYPE_2__ egrbufs; int /*<<< orphan*/ * rcvhdrtail_kvaddr; scalar_t__ rcvhdrqtailaddr_dma; scalar_t__ rcvhdrq_dma; } ;
struct TYPE_6__ {void* addr; scalar_t__ dma; int /*<<< orphan*/  len; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  rcvhdrq_size (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  sc_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

void hfi1_free_ctxtdata(struct hfi1_devdata *dd, struct hfi1_ctxtdata *rcd)
{
	u32 e;

	if (!rcd)
		return;

	if (rcd->rcvhdrq) {
		dma_free_coherent(&dd->pcidev->dev, rcvhdrq_size(rcd),
				  rcd->rcvhdrq, rcd->rcvhdrq_dma);
		rcd->rcvhdrq = NULL;
		if (rcd->rcvhdrtail_kvaddr) {
			dma_free_coherent(&dd->pcidev->dev, PAGE_SIZE,
					  (void *)rcd->rcvhdrtail_kvaddr,
					  rcd->rcvhdrqtailaddr_dma);
			rcd->rcvhdrtail_kvaddr = NULL;
		}
	}

	/* all the RcvArray entries should have been cleared by now */
	kfree(rcd->egrbufs.rcvtids);
	rcd->egrbufs.rcvtids = NULL;

	for (e = 0; e < rcd->egrbufs.alloced; e++) {
		if (rcd->egrbufs.buffers[e].dma)
			dma_free_coherent(&dd->pcidev->dev,
					  rcd->egrbufs.buffers[e].len,
					  rcd->egrbufs.buffers[e].addr,
					  rcd->egrbufs.buffers[e].dma);
	}
	kfree(rcd->egrbufs.buffers);
	rcd->egrbufs.alloced = 0;
	rcd->egrbufs.buffers = NULL;

	sc_free(rcd->sc);
	rcd->sc = NULL;

	vfree(rcd->subctxt_uregbase);
	vfree(rcd->subctxt_rcvegrbuf);
	vfree(rcd->subctxt_rcvhdr_base);
	kfree(rcd->opstats);

	rcd->subctxt_uregbase = NULL;
	rcd->subctxt_rcvegrbuf = NULL;
	rcd->subctxt_rcvhdr_base = NULL;
	rcd->opstats = NULL;
}