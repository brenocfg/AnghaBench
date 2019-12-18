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
struct xmit_buf {int /*<<< orphan*/ * pxmit_urb; } ;
struct _adapter {int /*<<< orphan*/  pnetdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kmemleak_not_leak (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int r8712_xmit_resource_alloc(struct _adapter *padapter,
			      struct xmit_buf *pxmitbuf)
{
	int i;

	for (i = 0; i < 8; i++) {
		pxmitbuf->pxmit_urb[i] = usb_alloc_urb(0, GFP_KERNEL);
		if (!pxmitbuf->pxmit_urb[i]) {
			netdev_err(padapter->pnetdev, "pxmitbuf->pxmit_urb[i] == NULL\n");
			return -ENOMEM;
		}
		kmemleak_not_leak(pxmitbuf->pxmit_urb[i]);
	}
	return 0;
}