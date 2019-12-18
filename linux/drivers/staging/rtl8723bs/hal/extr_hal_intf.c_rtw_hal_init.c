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
typedef  scalar_t__ uint ;
struct dvobj_priv {TYPE_3__* padapters; } ;
struct TYPE_4__ {int notch_filter; } ;
struct TYPE_5__ {scalar_t__ (* hal_init ) (struct adapter*) ;} ;
struct adapter {TYPE_1__ registrypriv; TYPE_2__ HalFunc; } ;
struct TYPE_6__ {int hw_init_completed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hal_init_c_ ; 
 struct dvobj_priv* adapter_to_dvobj (struct adapter*) ; 
 int /*<<< orphan*/  init_hw_mlme_ext (struct adapter*) ; 
 int /*<<< orphan*/  rtw_bb_rf_gain_offset (struct adapter*) ; 
 int /*<<< orphan*/  rtw_hal_init_opmode (struct adapter*) ; 
 int /*<<< orphan*/  rtw_hal_notch_filter (struct adapter*,int) ; 
 int /*<<< orphan*/  rtw_hal_reset_security_engine (struct adapter*) ; 
 int /*<<< orphan*/  rtw_sec_restore_wep_key (TYPE_3__*) ; 
 scalar_t__ stub1 (struct adapter*) ; 

uint rtw_hal_init(struct adapter *padapter)
{
	uint status;
	struct dvobj_priv *dvobj = adapter_to_dvobj(padapter);

	status = padapter->HalFunc.hal_init(padapter);

	if (status == _SUCCESS) {
		rtw_hal_init_opmode(padapter);

		dvobj->padapters->hw_init_completed = true;

		if (padapter->registrypriv.notch_filter == 1)
			rtw_hal_notch_filter(padapter, 1);

		rtw_hal_reset_security_engine(padapter);

		rtw_sec_restore_wep_key(dvobj->padapters);

		init_hw_mlme_ext(padapter);

		rtw_bb_rf_gain_offset(padapter);
	} else {
		dvobj->padapters->hw_init_completed = false;
		DBG_871X("rtw_hal_init: hal__init fail\n");
	}

	RT_TRACE(_module_hal_init_c_, _drv_err_, ("-rtl871x_hal_init:status = 0x%x\n", status));

	return status;

}