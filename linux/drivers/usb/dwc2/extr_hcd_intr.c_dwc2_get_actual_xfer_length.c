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
typedef  int u32 ;
struct dwc2_qtd {int ssplit_out_xfer_count; } ;
struct dwc2_hsotg {int dummy; } ;
struct dwc2_host_chan {int xfer_len; int start_pkt_count; int max_packet; TYPE_1__* qh; scalar_t__ ep_is_in; } ;
typedef  enum dwc2_halt_status { ____Placeholder_dwc2_halt_status } dwc2_halt_status ;
struct TYPE_2__ {scalar_t__ do_split; } ;

/* Variables and functions */
 int DWC2_HC_XFER_COMPLETE ; 
 int /*<<< orphan*/  HCTSIZ (int) ; 
 int TSIZ_PKTCNT_MASK ; 
 int TSIZ_PKTCNT_SHIFT ; 
 int TSIZ_XFERSIZE_MASK ; 
 int TSIZ_XFERSIZE_SHIFT ; 
 int dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 dwc2_get_actual_xfer_length(struct dwc2_hsotg *hsotg,
				       struct dwc2_host_chan *chan, int chnum,
				       struct dwc2_qtd *qtd,
				       enum dwc2_halt_status halt_status,
				       int *short_read)
{
	u32 hctsiz, count, length;

	hctsiz = dwc2_readl(hsotg, HCTSIZ(chnum));

	if (halt_status == DWC2_HC_XFER_COMPLETE) {
		if (chan->ep_is_in) {
			count = (hctsiz & TSIZ_XFERSIZE_MASK) >>
				TSIZ_XFERSIZE_SHIFT;
			length = chan->xfer_len - count;
			if (short_read)
				*short_read = (count != 0);
		} else if (chan->qh->do_split) {
			length = qtd->ssplit_out_xfer_count;
		} else {
			length = chan->xfer_len;
		}
	} else {
		/*
		 * Must use the hctsiz.pktcnt field to determine how much data
		 * has been transferred. This field reflects the number of
		 * packets that have been transferred via the USB. This is
		 * always an integral number of packets if the transfer was
		 * halted before its normal completion. (Can't use the
		 * hctsiz.xfersize field because that reflects the number of
		 * bytes transferred via the AHB, not the USB).
		 */
		count = (hctsiz & TSIZ_PKTCNT_MASK) >> TSIZ_PKTCNT_SHIFT;
		length = (chan->start_pkt_count - count) * chan->max_packet;
	}

	return length;
}