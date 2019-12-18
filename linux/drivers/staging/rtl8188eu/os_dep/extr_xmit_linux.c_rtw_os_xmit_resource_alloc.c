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
typedef  int /*<<< orphan*/  u32 ;
struct xmit_buf {int /*<<< orphan*/ * pxmit_urb; scalar_t__ dma_transfer_addr; int /*<<< orphan*/  pallocated_buf; int /*<<< orphan*/  pbuf; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_88E (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PTR_ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMITBUF_ALIGN_SZ ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rtw_os_xmit_resource_alloc(struct adapter *padapter,
			       struct xmit_buf *pxmitbuf, u32 alloc_sz)
{
	int i;

	pxmitbuf->pallocated_buf = kzalloc(alloc_sz, GFP_KERNEL);
	if (!pxmitbuf->pallocated_buf)
		return _FAIL;

	pxmitbuf->pbuf = PTR_ALIGN(pxmitbuf->pallocated_buf, XMITBUF_ALIGN_SZ);
	pxmitbuf->dma_transfer_addr = 0;

	for (i = 0; i < 8; i++) {
		pxmitbuf->pxmit_urb[i] = usb_alloc_urb(0, GFP_KERNEL);
		if (!pxmitbuf->pxmit_urb[i]) {
			DBG_88E("pxmitbuf->pxmit_urb[i]==NULL");
			return _FAIL;
		}
	}
	return _SUCCESS;
}