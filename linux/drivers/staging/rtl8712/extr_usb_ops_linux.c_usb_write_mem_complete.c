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
struct urb {int /*<<< orphan*/  status; scalar_t__ context; } ;
struct intf_hdl {scalar_t__ adapter; struct intf_priv* pintfpriv; } ;
struct io_queue {struct intf_hdl intf; } ;
struct intf_priv {int /*<<< orphan*/  io_retevt_comp; } ;
struct _adapter {int driver_stopped; int surprise_removed; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESHUTDOWN ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb_write_mem_complete(struct urb *purb)
{
	struct io_queue *pio_q = (struct io_queue *)purb->context;
	struct intf_hdl *pintf = &(pio_q->intf);
	struct intf_priv *pintfpriv = pintf->pintfpriv;
	struct _adapter *padapter = (struct _adapter *)pintf->adapter;

	if (purb->status != 0) {
		if (purb->status == (-ESHUTDOWN))
			padapter->driver_stopped = true;
		else
			padapter->surprise_removed = true;
	}
	complete(&pintfpriv->io_retevt_comp);
}