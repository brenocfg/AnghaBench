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
struct xmit_priv {int /*<<< orphan*/  ack_tx_mutex; struct xmit_buf* pcmd_xmitbuf; scalar_t__ pallocated_xmit_extbuf; scalar_t__ pxmit_extbuf; scalar_t__ xframe_ext_alloc_addr; scalar_t__ xframe_ext; scalar_t__ pallocated_xmitbuf; scalar_t__ pallocated_frame_buf; scalar_t__ pxmit_frame_buf; scalar_t__ pxmitbuf; struct adapter* adapter; } ;
struct xmit_frame {int dummy; } ;
struct xmit_buf {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int CMDBUF_MAX ; 
 scalar_t__ MAX_CMDBUF_SZ ; 
 scalar_t__ MAX_XMITBUF_SZ ; 
 scalar_t__ MAX_XMIT_EXTBUF_SZ ; 
 int NR_XMITBUFF ; 
 int NR_XMITFRAME ; 
 int NR_XMIT_EXTBUFF ; 
 scalar_t__ XMITBUF_ALIGN_SZ ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_free_hwxmits (struct adapter*) ; 
 int /*<<< orphan*/  rtw_hal_free_xmit_priv (struct adapter*) ; 
 int /*<<< orphan*/  rtw_os_xmit_complete (struct adapter*,struct xmit_frame*) ; 
 int /*<<< orphan*/  rtw_os_xmit_resource_free (struct adapter*,struct xmit_buf*,scalar_t__,int) ; 
 int /*<<< orphan*/  vfree (scalar_t__) ; 

void _rtw_free_xmit_priv(struct xmit_priv *pxmitpriv)
{
	int i;
	struct adapter *padapter = pxmitpriv->adapter;
	struct xmit_frame	*pxmitframe = (struct xmit_frame *) pxmitpriv->pxmit_frame_buf;
	struct xmit_buf *pxmitbuf = (struct xmit_buf *)pxmitpriv->pxmitbuf;

	rtw_hal_free_xmit_priv(padapter);

	if (!pxmitpriv->pxmit_frame_buf)
		return;

	for (i = 0; i < NR_XMITFRAME; i++) {
		rtw_os_xmit_complete(padapter, pxmitframe);

		pxmitframe++;
	}

	for (i = 0; i < NR_XMITBUFF; i++) {
		rtw_os_xmit_resource_free(padapter, pxmitbuf, (MAX_XMITBUF_SZ + XMITBUF_ALIGN_SZ), true);

		pxmitbuf++;
	}

	if (pxmitpriv->pallocated_frame_buf)
		vfree(pxmitpriv->pallocated_frame_buf);


	if (pxmitpriv->pallocated_xmitbuf)
		vfree(pxmitpriv->pallocated_xmitbuf);

	/* free xframe_ext queue,  the same count as extbuf  */
	pxmitframe = (struct xmit_frame *)pxmitpriv->xframe_ext;
	if (pxmitframe) {
		for (i = 0; i < NR_XMIT_EXTBUFF; i++) {
			rtw_os_xmit_complete(padapter, pxmitframe);
			pxmitframe++;
		}
	}
	if (pxmitpriv->xframe_ext_alloc_addr)
		vfree(pxmitpriv->xframe_ext_alloc_addr);

	/*  free xmit extension buff */
	pxmitbuf = (struct xmit_buf *)pxmitpriv->pxmit_extbuf;
	for (i = 0; i < NR_XMIT_EXTBUFF; i++) {
		rtw_os_xmit_resource_free(padapter, pxmitbuf, (MAX_XMIT_EXTBUF_SZ + XMITBUF_ALIGN_SZ), true);

		pxmitbuf++;
	}

	if (pxmitpriv->pallocated_xmit_extbuf) {
		vfree(pxmitpriv->pallocated_xmit_extbuf);
	}

	for (i = 0; i < CMDBUF_MAX; i++) {
		pxmitbuf = &pxmitpriv->pcmd_xmitbuf[i];
		if (pxmitbuf)
			rtw_os_xmit_resource_free(padapter, pxmitbuf, MAX_CMDBUF_SZ+XMITBUF_ALIGN_SZ, true);
	}

	rtw_free_hwxmits(padapter);

	mutex_destroy(&pxmitpriv->ack_tx_mutex);
}