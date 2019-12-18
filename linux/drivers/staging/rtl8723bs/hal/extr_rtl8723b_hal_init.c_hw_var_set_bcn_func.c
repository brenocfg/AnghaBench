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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int EN_BCN_FUNCTION ; 
 int EN_TXBCN_RPT ; 
 scalar_t__ REG_BCN_CTRL ; 
 int rtw_read8 (struct adapter*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_write8 (struct adapter*,scalar_t__,int) ; 

__attribute__((used)) static void hw_var_set_bcn_func(struct adapter *padapter, u8 variable, u8 *val)
{
	u32 bcn_ctrl_reg;

	bcn_ctrl_reg = REG_BCN_CTRL;

	if (*(u8 *)val)
		rtw_write8(padapter, bcn_ctrl_reg, (EN_BCN_FUNCTION | EN_TXBCN_RPT));
	else {
		u8 val8;
		val8 = rtw_read8(padapter, bcn_ctrl_reg);
		val8 &= ~(EN_BCN_FUNCTION | EN_TXBCN_RPT);

		/*  Always enable port0 beacon function for PSTDMA */
		if (REG_BCN_CTRL == bcn_ctrl_reg)
			val8 |= EN_BCN_FUNCTION;

		rtw_write8(padapter, bcn_ctrl_reg, val8);
	}
}