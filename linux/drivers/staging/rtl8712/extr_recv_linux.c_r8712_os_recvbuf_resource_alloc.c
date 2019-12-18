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
struct recv_buf {int irp_pending; scalar_t__ len; scalar_t__ transfer_len; int /*<<< orphan*/ * pend; int /*<<< orphan*/ * ptail; int /*<<< orphan*/ * phead; int /*<<< orphan*/ * pdata; int /*<<< orphan*/ * pbuf; int /*<<< orphan*/ * pallocated_buf; int /*<<< orphan*/ * pskb; int /*<<< orphan*/  purb; } ;
struct _adapter {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int r8712_os_recvbuf_resource_alloc(struct _adapter *padapter,
				    struct recv_buf *precvbuf)
{
	int res = 0;

	precvbuf->irp_pending = false;
	precvbuf->purb = usb_alloc_urb(0, GFP_KERNEL);
	if (!precvbuf->purb)
		res = -ENOMEM;
	precvbuf->pskb = NULL;
	precvbuf->pallocated_buf = NULL;
	precvbuf->pbuf = NULL;
	precvbuf->pdata = NULL;
	precvbuf->phead = NULL;
	precvbuf->ptail = NULL;
	precvbuf->pend = NULL;
	precvbuf->transfer_len = 0;
	precvbuf->len = 0;
	return res;
}