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
struct xmit_frame {int /*<<< orphan*/  buf_addr; int /*<<< orphan*/ * pxmit_urb; struct xmit_buf* pxmitbuf; } ;
struct xmit_buf {struct xmit_frame* priv_data; int /*<<< orphan*/  pbuf; int /*<<< orphan*/ * pxmit_urb; } ;

/* Variables and functions */

void xmitframe_xmitbuf_attach(struct xmit_frame *pxmitframe,
			struct xmit_buf *pxmitbuf)
{
	/* pxmitbuf attach to pxmitframe */
	pxmitframe->pxmitbuf = pxmitbuf;
	/* urb and irp connection */
	pxmitframe->pxmit_urb[0] = pxmitbuf->pxmit_urb[0];
	/* buffer addr assoc */
	pxmitframe->buf_addr = pxmitbuf->pbuf;
	/* pxmitframe attach to pxmitbuf */
	pxmitbuf->priv_data = pxmitframe;
}