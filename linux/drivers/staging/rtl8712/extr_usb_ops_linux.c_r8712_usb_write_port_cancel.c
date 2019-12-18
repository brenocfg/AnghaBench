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
struct xmit_buf {scalar_t__* pxmit_urb; } ;
struct TYPE_2__ {scalar_t__ pxmitbuf; } ;
struct _adapter {TYPE_1__ xmitpriv; } ;

/* Variables and functions */
 int NR_XMITBUFF ; 
 int /*<<< orphan*/  usb_kill_urb (scalar_t__) ; 

void r8712_usb_write_port_cancel(struct _adapter *padapter)
{
	int i, j;
	struct xmit_buf	*pxmitbuf = (struct xmit_buf *)
				     padapter->xmitpriv.pxmitbuf;

	for (i = 0; i < NR_XMITBUFF; i++) {
		for (j = 0; j < 8; j++) {
			if (pxmitbuf->pxmit_urb[j])
				usb_kill_urb(pxmitbuf->pxmit_urb[j]);
		}
		pxmitbuf++;
	}
}