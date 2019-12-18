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
struct ScsiReqBlk {int flag; TYPE_2__* segment_x; int /*<<< orphan*/  xferred; int /*<<< orphan*/  total_xfer_length; } ;
struct AdapterCtlBlk {TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  address; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AUTO_REQSENSE ; 
 int /*<<< orphan*/  DBG_SG ; 
 int DC395x_MAX_SG_LISTENTRY ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintkdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pci_unmap_srb_sense(struct AdapterCtlBlk *acb,
		struct ScsiReqBlk *srb)
{
	if (!(srb->flag & AUTO_REQSENSE))
		return;
	/* Unmap sense buffer */
	dprintkdbg(DBG_SG, "pci_unmap_srb_sense: buffer=%08x\n",
	       srb->segment_x[0].address);
	dma_unmap_single(&acb->dev->dev, srb->segment_x[0].address,
			 srb->segment_x[0].length, DMA_FROM_DEVICE);
	/* Restore SG stuff */
	srb->total_xfer_length = srb->xferred;
	srb->segment_x[0].address =
	    srb->segment_x[DC395x_MAX_SG_LISTENTRY - 1].address;
	srb->segment_x[0].length =
	    srb->segment_x[DC395x_MAX_SG_LISTENTRY - 1].length;
}