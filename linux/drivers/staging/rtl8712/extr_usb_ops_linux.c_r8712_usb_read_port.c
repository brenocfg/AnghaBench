#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct usb_device {int dummy; } ;
struct urb {int dummy; } ;
struct recv_priv {int /*<<< orphan*/  free_recv_skb_queue; } ;
struct recv_buf {scalar_t__ pbuf; struct urb* purb; TYPE_2__* pskb; void* pend; void* ptail; scalar_t__ pdata; int /*<<< orphan*/  phead; } ;
struct intf_priv {scalar_t__ intf_dev; } ;
struct intf_hdl {struct intf_priv* pintfpriv; } ;
struct dvobj_priv {struct usb_device* pusbdev; struct _adapter* padapter; } ;
struct TYPE_7__ {scalar_t__ pnp_bstop_trx; } ;
struct _adapter {int /*<<< orphan*/  pnetdev; TYPE_1__ pwrctrlpriv; scalar_t__ surprise_removed; scalar_t__ driver_stopped; struct recv_priv recvpriv; } ;
typedef  int addr_t ;
struct TYPE_8__ {scalar_t__ data; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ MAX_RECVBUF_SZ ; 
 int RECVBUFF_ALIGN_SZ ; 
 int _FAIL ; 
 int _SUCCESS ; 
 unsigned int ffaddr2pipehdl (struct dvobj_priv*,int) ; 
 TYPE_2__* netdev_alloc_skb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  r8712_init_recvbuf (struct _adapter*,struct recv_buf*) ; 
 int /*<<< orphan*/  r8712_usb_read_port_complete ; 
 TYPE_2__* skb_dequeue (int /*<<< orphan*/ *) ; 
 void* skb_end_pointer (TYPE_2__*) ; 
 int /*<<< orphan*/  skb_reserve (TYPE_2__*,int) ; 
 void* skb_tail_pointer (TYPE_2__*) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,struct usb_device*,unsigned int,scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct recv_buf*) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

u32 r8712_usb_read_port(struct intf_hdl *pintfhdl, u32 addr, u32 cnt, u8 *rmem)
{
	unsigned int pipe;
	int err;
	u32 tmpaddr = 0;
	int alignment = 0;
	u32 ret = _SUCCESS;
	struct urb *purb = NULL;
	struct recv_buf	*precvbuf = (struct recv_buf *)rmem;
	struct intf_priv *pintfpriv = pintfhdl->pintfpriv;
	struct dvobj_priv *pdvobj = (struct dvobj_priv *)pintfpriv->intf_dev;
	struct _adapter *adapter = pdvobj->padapter;
	struct recv_priv *precvpriv = &adapter->recvpriv;
	struct usb_device *pusbd = pdvobj->pusbdev;

	if (adapter->driver_stopped || adapter->surprise_removed ||
	    adapter->pwrctrlpriv.pnp_bstop_trx || !precvbuf)
		return _FAIL;
	r8712_init_recvbuf(adapter, precvbuf);
	/* Try to use skb from the free queue */
	precvbuf->pskb = skb_dequeue(&precvpriv->free_recv_skb_queue);

	if (!precvbuf->pskb) {
		precvbuf->pskb = netdev_alloc_skb(adapter->pnetdev,
				 MAX_RECVBUF_SZ + RECVBUFF_ALIGN_SZ);
		if (!precvbuf->pskb)
			return _FAIL;
		tmpaddr = (addr_t)precvbuf->pskb->data;
		alignment = tmpaddr & (RECVBUFF_ALIGN_SZ - 1);
		skb_reserve(precvbuf->pskb,
			    (RECVBUFF_ALIGN_SZ - alignment));
		precvbuf->phead = precvbuf->pskb->head;
		precvbuf->pdata = precvbuf->pskb->data;
		precvbuf->ptail = skb_tail_pointer(precvbuf->pskb);
		precvbuf->pend = skb_end_pointer(precvbuf->pskb);
		precvbuf->pbuf = precvbuf->pskb->data;
	} else { /* skb is reused */
		precvbuf->phead = precvbuf->pskb->head;
		precvbuf->pdata = precvbuf->pskb->data;
		precvbuf->ptail = skb_tail_pointer(precvbuf->pskb);
		precvbuf->pend = skb_end_pointer(precvbuf->pskb);
		precvbuf->pbuf = precvbuf->pskb->data;
	}
	purb = precvbuf->purb;
	/* translate DMA FIFO addr to pipehandle */
	pipe = ffaddr2pipehdl(pdvobj, addr);
	usb_fill_bulk_urb(purb, pusbd, pipe,
			  precvbuf->pbuf, MAX_RECVBUF_SZ,
			  r8712_usb_read_port_complete,
			  precvbuf);
	err = usb_submit_urb(purb, GFP_ATOMIC);
	if ((err) && (err != (-EPERM)))
		ret = _FAIL;
	return ret;
}