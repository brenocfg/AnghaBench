#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_7__ {int bSurpriseRemoved; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_RATE ; 
 int /*<<< orphan*/  EE_9346CR ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int _EEDI ; 
 int _EEDO ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_eeprom_c_ ; 
 int /*<<< orphan*/  down_clk (TYPE_1__*,int*) ; 
 int rtw_read8 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_clk (TYPE_1__*,int*) ; 

void shift_out_bits(_adapter *padapter, u16 data, u16 count)
{
	u16 x, mask;
_func_enter_;

	if (padapter->bSurpriseRemoved == true) {
		RT_TRACE(_module_rtl871x_eeprom_c_, _drv_err_, ("padapter->bSurpriseRemoved==true"));
		goto out;
	}
	mask = 0x01 << (count - 1);
	x = rtw_read8(padapter, EE_9346CR);

	x &= ~(_EEDO | _EEDI);

	do {
		x &= ~_EEDI;
		if (data & mask)
			x |= _EEDI;
		if (padapter->bSurpriseRemoved == true) {
		RT_TRACE(_module_rtl871x_eeprom_c_, _drv_err_, ("padapter->bSurpriseRemoved==true"));
		goto out;
		}
		rtw_write8(padapter, EE_9346CR, (u8)x);
		udelay(CLOCK_RATE);
		up_clk(padapter, &x);
		down_clk(padapter, &x);
		mask = mask >> 1;
	} while (mask);
	if (padapter->bSurpriseRemoved == true) {
		RT_TRACE(_module_rtl871x_eeprom_c_, _drv_err_, ("padapter->bSurpriseRemoved==true"));
		goto out;
	}
	x &= ~_EEDI;
	rtw_write8(padapter, EE_9346CR, (u8)x);
out:
_func_exit_;
}