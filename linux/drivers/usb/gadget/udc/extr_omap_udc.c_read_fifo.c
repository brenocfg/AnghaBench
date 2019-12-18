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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_4__ {scalar_t__ length; scalar_t__ actual; int /*<<< orphan*/  status; int /*<<< orphan*/ * buf; } ;
struct omap_req {TYPE_2__ req; } ;
struct TYPE_3__ {unsigned int maxpacket; } ;
struct omap_ep {int double_buf; int fnf; int /*<<< orphan*/  bEndpointAddress; TYPE_1__ ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOVERFLOW ; 
 int FIFO_EMPTY ; 
 int /*<<< orphan*/  UDC_DATA ; 
 int UDC_EP_HALTED ; 
 int UDC_FIFO_FULL ; 
 int /*<<< orphan*/  UDC_RXFSTAT ; 
 int /*<<< orphan*/  UDC_STAT_FLG ; 
 int /*<<< orphan*/  done (struct omap_ep*,struct omap_req*,int /*<<< orphan*/ ) ; 
 void* omap_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetchw (int /*<<< orphan*/ *) ; 
 unsigned int read_packet (int /*<<< orphan*/ *,struct omap_req*,unsigned int) ; 

__attribute__((used)) static int read_fifo(struct omap_ep *ep, struct omap_req *req)
{
	u8		*buf;
	unsigned	count, avail;
	int		is_last;

	buf = req->req.buf + req->req.actual;
	prefetchw(buf);

	for (;;) {
		u16	ep_stat = omap_readw(UDC_STAT_FLG);

		is_last = 0;
		if (ep_stat & FIFO_EMPTY) {
			if (!ep->double_buf)
				break;
			ep->fnf = 1;
		}
		if (ep_stat & UDC_EP_HALTED)
			break;

		if (ep_stat & UDC_FIFO_FULL)
			avail = ep->ep.maxpacket;
		else  {
			avail = omap_readw(UDC_RXFSTAT);
			ep->fnf = ep->double_buf;
		}
		count = read_packet(buf, req, avail);

		/* partial packet reads may not be errors */
		if (count < ep->ep.maxpacket) {
			is_last = 1;
			/* overflowed this request?  flush extra data */
			if (count != avail) {
				req->req.status = -EOVERFLOW;
				avail -= count;
				while (avail--)
					omap_readw(UDC_DATA);
			}
		} else if (req->req.length == req->req.actual)
			is_last = 1;
		else
			is_last = 0;

		if (!ep->bEndpointAddress)
			break;
		if (is_last)
			done(ep, req, 0);
		break;
	}
	return is_last;
}