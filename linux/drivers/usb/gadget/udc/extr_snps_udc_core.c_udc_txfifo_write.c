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
typedef  int u32 ;
struct usb_request {int actual; unsigned int length; int /*<<< orphan*/ * buf; } ;
struct TYPE_3__ {unsigned int maxpacket; } ;
struct udc_ep {TYPE_2__* regs; int /*<<< orphan*/ * txfifo; TYPE_1__ ep; } ;
struct TYPE_4__ {int /*<<< orphan*/  confirm; } ;

/* Variables and functions */
 int UDC_BITS_PER_BYTE_SHIFT ; 
 unsigned int UDC_DWORD_BYTES ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
udc_txfifo_write(struct udc_ep *ep, struct usb_request *req)
{
	u8			*req_buf;
	u32			*buf;
	int			i, j;
	unsigned		bytes = 0;
	unsigned		remaining = 0;

	if (!req || !ep)
		return;

	req_buf = req->buf + req->actual;
	prefetch(req_buf);
	remaining = req->length - req->actual;

	buf = (u32 *) req_buf;

	bytes = ep->ep.maxpacket;
	if (bytes > remaining)
		bytes = remaining;

	/* dwords first */
	for (i = 0; i < bytes / UDC_DWORD_BYTES; i++)
		writel(*(buf + i), ep->txfifo);

	/* remaining bytes must be written by byte access */
	for (j = 0; j < bytes % UDC_DWORD_BYTES; j++) {
		writeb((u8)(*(buf + i) >> (j << UDC_BITS_PER_BYTE_SHIFT)),
							ep->txfifo);
	}

	/* dummy write confirm */
	writel(0, &ep->regs->confirm);
}