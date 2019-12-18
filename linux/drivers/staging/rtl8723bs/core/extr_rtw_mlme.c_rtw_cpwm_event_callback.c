#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct reportpwrstate_parm {int /*<<< orphan*/  state; } ;
struct adapter {int dummy; } ;
struct TYPE_2__ {scalar_t__ cpwm_tog; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 TYPE_1__* adapter_to_pwrctl (struct adapter*) ; 
 int /*<<< orphan*/  cpwm_int_hdl (struct adapter*,struct reportpwrstate_parm*) ; 

void rtw_cpwm_event_callback(struct adapter *padapter, u8 *pbuf)
{
	struct reportpwrstate_parm *preportpwrstate;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("+rtw_cpwm_event_callback !!!\n"));
	preportpwrstate = (struct reportpwrstate_parm *)pbuf;
	preportpwrstate->state |= (u8)(adapter_to_pwrctl(padapter)->cpwm_tog + 0x80);
	cpwm_int_hdl(padapter, preportpwrstate);
}