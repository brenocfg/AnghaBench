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
typedef  int u32 ;
struct xmit_priv {int ack_tx; int /*<<< orphan*/  ack_tx_mutex; } ;
struct xmit_frame {int ack_report; } ;
struct adapter {scalar_t__ bDriverStopped; scalar_t__ bSurpriseRemoved; struct xmit_priv xmitpriv; } ;
typedef  int s32 ;

/* Variables and functions */
 int _FAIL ; 
 scalar_t__ _SUCCESS ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rtw_ack_tx_wait (struct xmit_priv*,int) ; 
 scalar_t__ rtw_hal_mgnt_xmit (struct adapter*,struct xmit_frame*) ; 

__attribute__((used)) static s32 dump_mgntframe_and_wait_ack(struct adapter *padapter,
				       struct xmit_frame *pmgntframe)
{
	s32 ret = _FAIL;
	u32 timeout_ms = 500;/*   500ms */
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;

	if (padapter->bSurpriseRemoved || padapter->bDriverStopped)
		return -1;

	if (mutex_lock_interruptible(&pxmitpriv->ack_tx_mutex))
		return _FAIL;
	pxmitpriv->ack_tx = true;

	pmgntframe->ack_report = 1;
	if (rtw_hal_mgnt_xmit(padapter, pmgntframe) == _SUCCESS)
		ret = rtw_ack_tx_wait(pxmitpriv, timeout_ms);

	pxmitpriv->ack_tx = false;
	mutex_unlock(&pxmitpriv->ack_tx_mutex);

	return ret;
}