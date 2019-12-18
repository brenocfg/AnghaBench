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
typedef  size_t u32 ;
struct dwc2_hsotg {int /*<<< orphan*/  dev; struct dwc2_host_chan** hc_ptr_array; } ;
struct dwc2_host_chan {size_t xfer_buf; size_t xfer_count; int /*<<< orphan*/  data_pid_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRXSTSP ; 
 size_t GRXSTS_BYTECNT_MASK ; 
 size_t GRXSTS_BYTECNT_SHIFT ; 
 size_t GRXSTS_DPID_MASK ; 
 size_t GRXSTS_DPID_SHIFT ; 
 size_t GRXSTS_HCHNUM_MASK ; 
 size_t GRXSTS_HCHNUM_SHIFT ; 
#define  GRXSTS_PKTSTS_DATATOGGLEERR 131 
#define  GRXSTS_PKTSTS_HCHHALTED 130 
#define  GRXSTS_PKTSTS_HCHIN 129 
#define  GRXSTS_PKTSTS_HCHIN_XFER_COMP 128 
 size_t GRXSTS_PKTSTS_MASK ; 
 size_t GRXSTS_PKTSTS_SHIFT ; 
 scalar_t__ dbg_perio () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dwc2_read_packet (struct dwc2_hsotg*,size_t,size_t) ; 
 size_t dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc2_rx_fifo_level_intr(struct dwc2_hsotg *hsotg)
{
	u32 grxsts, chnum, bcnt, dpid, pktsts;
	struct dwc2_host_chan *chan;

	if (dbg_perio())
		dev_vdbg(hsotg->dev, "--RxFIFO Level Interrupt--\n");

	grxsts = dwc2_readl(hsotg, GRXSTSP);
	chnum = (grxsts & GRXSTS_HCHNUM_MASK) >> GRXSTS_HCHNUM_SHIFT;
	chan = hsotg->hc_ptr_array[chnum];
	if (!chan) {
		dev_err(hsotg->dev, "Unable to get corresponding channel\n");
		return;
	}

	bcnt = (grxsts & GRXSTS_BYTECNT_MASK) >> GRXSTS_BYTECNT_SHIFT;
	dpid = (grxsts & GRXSTS_DPID_MASK) >> GRXSTS_DPID_SHIFT;
	pktsts = (grxsts & GRXSTS_PKTSTS_MASK) >> GRXSTS_PKTSTS_SHIFT;

	/* Packet Status */
	if (dbg_perio()) {
		dev_vdbg(hsotg->dev, "    Ch num = %d\n", chnum);
		dev_vdbg(hsotg->dev, "    Count = %d\n", bcnt);
		dev_vdbg(hsotg->dev, "    DPID = %d, chan.dpid = %d\n", dpid,
			 chan->data_pid_start);
		dev_vdbg(hsotg->dev, "    PStatus = %d\n", pktsts);
	}

	switch (pktsts) {
	case GRXSTS_PKTSTS_HCHIN:
		/* Read the data into the host buffer */
		if (bcnt > 0) {
			dwc2_read_packet(hsotg, chan->xfer_buf, bcnt);

			/* Update the HC fields for the next packet received */
			chan->xfer_count += bcnt;
			chan->xfer_buf += bcnt;
		}
		break;
	case GRXSTS_PKTSTS_HCHIN_XFER_COMP:
	case GRXSTS_PKTSTS_DATATOGGLEERR:
	case GRXSTS_PKTSTS_HCHHALTED:
		/* Handled in interrupt, just ignore data */
		break;
	default:
		dev_err(hsotg->dev,
			"RxFIFO Level Interrupt: Unknown status %d\n", pktsts);
		break;
	}
}