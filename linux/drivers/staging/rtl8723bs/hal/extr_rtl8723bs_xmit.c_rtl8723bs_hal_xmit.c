#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xmit_priv {int /*<<< orphan*/  SdioXmitStart; int /*<<< orphan*/  tx_drop; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int ether_type; int dhcp_pkt; int /*<<< orphan*/  priority; int /*<<< orphan*/  qsel; } ;
struct xmit_frame {scalar_t__ frame_tag; TYPE_1__ attrib; } ;
struct TYPE_5__ {scalar_t__ bBusyTraffic; } ;
struct TYPE_6__ {TYPE_2__ LinkDetectInfo; } ;
struct adapter {TYPE_3__ mlmepriv; struct xmit_priv xmitpriv; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ DATA_FRAMETAG ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hal_xmit_c_ ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_free_xmitframe (struct xmit_priv*,struct xmit_frame*) ; 
 int /*<<< orphan*/  rtw_issue_addbareq_cmd (struct adapter*,struct xmit_frame*) ; 
 scalar_t__ rtw_xmitframe_enqueue (struct adapter*,struct xmit_frame*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

s32 rtl8723bs_hal_xmit(
	struct adapter *padapter, struct xmit_frame *pxmitframe
)
{
	struct xmit_priv *pxmitpriv;
	s32 err;


	pxmitframe->attrib.qsel = pxmitframe->attrib.priority;
	pxmitpriv = &padapter->xmitpriv;

	if (
		(pxmitframe->frame_tag == DATA_FRAMETAG) &&
		(pxmitframe->attrib.ether_type != 0x0806) &&
		(pxmitframe->attrib.ether_type != 0x888e) &&
		(pxmitframe->attrib.dhcp_pkt != 1)
	) {
		if (padapter->mlmepriv.LinkDetectInfo.bBusyTraffic)
			rtw_issue_addbareq_cmd(padapter, pxmitframe);
	}

	spin_lock_bh(&pxmitpriv->lock);
	err = rtw_xmitframe_enqueue(padapter, pxmitframe);
	spin_unlock_bh(&pxmitpriv->lock);
	if (err != _SUCCESS) {
		RT_TRACE(_module_hal_xmit_c_, _drv_err_, ("rtl8723bs_hal_xmit: enqueue xmitframe fail\n"));
		rtw_free_xmitframe(pxmitpriv, pxmitframe);

		pxmitpriv->tx_drop++;
		return true;
	}

	complete(&pxmitpriv->SdioXmitStart);

	return false;
}