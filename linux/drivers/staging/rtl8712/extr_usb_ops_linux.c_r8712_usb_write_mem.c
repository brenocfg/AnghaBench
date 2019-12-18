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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct usb_device {int dummy; } ;
struct urb {int dummy; } ;
struct io_queue {int dummy; } ;
struct intf_priv {int /*<<< orphan*/  io_retevt_comp; struct urb* piorw_urb; scalar_t__ intf_dev; } ;
struct intf_hdl {struct intf_priv* pintfpriv; scalar_t__ adapter; } ;
struct dvobj_priv {struct usb_device* pusbdev; } ;
struct TYPE_2__ {scalar_t__ pnp_bstop_trx; } ;
struct _adapter {TYPE_1__ pwrctrlpriv; scalar_t__ surprise_removed; scalar_t__ driver_stopped; struct io_queue* pio_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned int ffaddr2pipehdl (struct dvobj_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,struct usb_device*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct io_queue*) ; 
 int /*<<< orphan*/  usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_write_mem_complete ; 
 int /*<<< orphan*/  wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

void r8712_usb_write_mem(struct intf_hdl *pintfhdl, u32 addr, u32 cnt, u8 *wmem)
{
	unsigned int pipe;
	struct _adapter *padapter = (struct _adapter *)pintfhdl->adapter;
	struct intf_priv *pintfpriv = pintfhdl->pintfpriv;
	struct io_queue *pio_queue = padapter->pio_queue;
	struct dvobj_priv *pdvobj = (struct dvobj_priv *)pintfpriv->intf_dev;
	struct usb_device *pusbd = pdvobj->pusbdev;
	struct urb *piorw_urb = pintfpriv->piorw_urb;

	if ((padapter->driver_stopped) || (padapter->surprise_removed) ||
	    (padapter->pwrctrlpriv.pnp_bstop_trx))
		return;
	/* translate DMA FIFO addr to pipehandle */
	pipe = ffaddr2pipehdl(pdvobj, addr);
	if (pipe == 0)
		return;
	usb_fill_bulk_urb(piorw_urb, pusbd, pipe,
			  wmem, cnt, usb_write_mem_complete,
			  pio_queue);
	usb_submit_urb(piorw_urb, GFP_ATOMIC);
	wait_for_completion_interruptible(&pintfpriv->io_retevt_comp);
}