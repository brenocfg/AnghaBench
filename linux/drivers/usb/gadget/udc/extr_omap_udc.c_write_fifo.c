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
struct TYPE_4__ {scalar_t__ length; scalar_t__ actual; int /*<<< orphan*/  zero; int /*<<< orphan*/ * buf; } ;
struct omap_req {TYPE_2__ req; } ;
struct TYPE_3__ {unsigned int maxpacket; } ;
struct omap_ep {int ackwait; TYPE_1__ ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDC_CTRL ; 
 int UDC_FIFO_UNWRITABLE ; 
 int /*<<< orphan*/  UDC_SET_FIFO_EN ; 
 int /*<<< orphan*/  UDC_STAT_FLG ; 
 int /*<<< orphan*/  done (struct omap_ep*,struct omap_req*,int /*<<< orphan*/ ) ; 
 int omap_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ *) ; 
 unsigned int write_packet (int /*<<< orphan*/ *,struct omap_req*,unsigned int) ; 

__attribute__((used)) static int write_fifo(struct omap_ep *ep, struct omap_req *req)
{
	u8		*buf;
	unsigned	count;
	int		is_last;
	u16		ep_stat;

	buf = req->req.buf + req->req.actual;
	prefetch(buf);

	/* PIO-IN isn't double buffered except for iso */
	ep_stat = omap_readw(UDC_STAT_FLG);
	if (ep_stat & UDC_FIFO_UNWRITABLE)
		return 0;

	count = ep->ep.maxpacket;
	count = write_packet(buf, req, count);
	omap_writew(UDC_SET_FIFO_EN, UDC_CTRL);
	ep->ackwait = 1;

	/* last packet is often short (sometimes a zlp) */
	if (count != ep->ep.maxpacket)
		is_last = 1;
	else if (req->req.length == req->req.actual
			&& !req->req.zero)
		is_last = 1;
	else
		is_last = 0;

	/* NOTE:  requests complete when all IN data is in a
	 * FIFO (or sometimes later, if a zlp was needed).
	 * Use usb_ep_fifo_status() where needed.
	 */
	if (is_last)
		done(ep, req, 0);
	return is_last;
}