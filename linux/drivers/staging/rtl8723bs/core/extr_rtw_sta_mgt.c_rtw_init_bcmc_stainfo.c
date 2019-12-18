#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct tx_servq {int dummy; } ;
struct sta_priv {int dummy; } ;
struct TYPE_4__ {struct tx_servq be_q; } ;
struct sta_info {int mac_id; TYPE_1__ sta_xmitpriv; } ;
struct adapter {struct sta_priv stapriv; } ;
struct TYPE_5__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; } ;
typedef  TYPE_2__ NDIS_802_11_MAC_ADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_rtl871x_sta_mgt_c_ ; 
 struct sta_info* rtw_alloc_stainfo (struct sta_priv*,TYPE_2__) ; 

u32 rtw_init_bcmc_stainfo(struct adapter *padapter)
{

	struct sta_info *psta;
	struct tx_servq	*ptxservq;
	u32 res = _SUCCESS;
	NDIS_802_11_MAC_ADDRESS	bcast_addr = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

	struct	sta_priv *pstapriv = &padapter->stapriv;
	/* struct __queue	*pstapending = &padapter->xmitpriv.bm_pending; */

	psta = rtw_alloc_stainfo(pstapriv, bcast_addr);

	if (!psta) {
		res = _FAIL;
		RT_TRACE(_module_rtl871x_sta_mgt_c_, _drv_err_, ("rtw_alloc_stainfo fail"));
		goto exit;
	}

	/*  default broadcast & multicast use macid 1 */
	psta->mac_id = 1;

	ptxservq = &(psta->sta_xmitpriv.be_q);
exit:
	return _SUCCESS;
}