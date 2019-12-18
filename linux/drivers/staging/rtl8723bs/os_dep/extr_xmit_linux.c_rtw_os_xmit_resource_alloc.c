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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct xmit_buf {scalar_t__ pallocated_buf; int /*<<< orphan*/ * pbuf; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  SIZE_PTR ;

/* Variables and functions */
 scalar_t__ N_BYTE_ALIGMENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMITBUF_ALIGN_SZ ; 
 int _FAIL ; 
 int _SUCCESS ; 
 scalar_t__ rtw_zmalloc (scalar_t__) ; 

int rtw_os_xmit_resource_alloc(struct adapter *padapter, struct xmit_buf *pxmitbuf, u32 alloc_sz, u8 flag)
{
	if (alloc_sz > 0) {
		pxmitbuf->pallocated_buf = rtw_zmalloc(alloc_sz);
		if (!pxmitbuf->pallocated_buf)
			return _FAIL;

		pxmitbuf->pbuf = (u8 *)N_BYTE_ALIGMENT((SIZE_PTR)(pxmitbuf->pallocated_buf), XMITBUF_ALIGN_SZ);
	}

	return _SUCCESS;
}