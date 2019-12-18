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
typedef  int u32 ;
struct xmit_priv {int ack_tx; int /*<<< orphan*/  ack_tx_mutex; scalar_t__ seq_no; } ;
struct xmit_frame {int ack_report; int /*<<< orphan*/  pxmitbuf; } ;
struct adapter {struct xmit_priv xmitpriv; scalar_t__ bDriverStopped; scalar_t__ bSurpriseRemoved; } ;
typedef  int s32 ;

/* Variables and functions */
 int _FAIL ; 
 scalar_t__ _SUCCESS ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rtw_ack_tx_wait (struct xmit_priv*,int) ; 
 int /*<<< orphan*/  rtw_free_xmitbuf (struct xmit_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_free_xmitframe (struct xmit_priv*,struct xmit_frame*) ; 
 scalar_t__ rtw_hal_mgnt_xmit (struct adapter*,struct xmit_frame*) ; 

s32 dump_mgntframe_and_wait_ack(struct adapter *padapter, struct xmit_frame *pmgntframe)
{
	static u8 seq_no;
	s32 ret = _FAIL;
	u32 timeout_ms = 500;/*   500ms */
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;

	if (padapter->bSurpriseRemoved ||
		padapter->bDriverStopped) {
		rtw_free_xmitbuf(&padapter->xmitpriv, pmgntframe->pxmitbuf);
		rtw_free_xmitframe(&padapter->xmitpriv, pmgntframe);
		return -1;
	}

	if (mutex_lock_interruptible(&pxmitpriv->ack_tx_mutex) == 0) {
		pxmitpriv->ack_tx = true;
		pxmitpriv->seq_no = seq_no++;
		pmgntframe->ack_report = 1;
		if (rtw_hal_mgnt_xmit(padapter, pmgntframe) == _SUCCESS)
			ret = rtw_ack_tx_wait(pxmitpriv, timeout_ms);

		pxmitpriv->ack_tx = false;
		mutex_unlock(&pxmitpriv->ack_tx_mutex);
	}

	return ret;
}