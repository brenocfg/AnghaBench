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
struct xmit_frame {int /*<<< orphan*/  pxmitbuf; } ;
struct adapter {int /*<<< orphan*/  xmitpriv; scalar_t__ bDriverStopped; scalar_t__ bSurpriseRemoved; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_free_xmitbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_free_xmitframe (int /*<<< orphan*/ *,struct xmit_frame*) ; 
 int /*<<< orphan*/  rtw_hal_mgnt_xmit (struct adapter*,struct xmit_frame*) ; 

void dump_mgntframe(struct adapter *padapter, struct xmit_frame *pmgntframe)
{
	if (padapter->bSurpriseRemoved ||
		padapter->bDriverStopped) {
		rtw_free_xmitbuf(&padapter->xmitpriv, pmgntframe->pxmitbuf);
		rtw_free_xmitframe(&padapter->xmitpriv, pmgntframe);
		return;
	}

	rtw_hal_mgnt_xmit(padapter, pmgntframe);
}