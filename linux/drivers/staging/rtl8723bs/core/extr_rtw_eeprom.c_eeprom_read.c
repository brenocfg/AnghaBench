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
typedef  int u32 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int eeprom_read16 (int /*<<< orphan*/ *,int) ; 

u8 eeprom_read(_adapter *padapter, u32 addr_off, u8 sz, u8 *rbuf)
{
	u8 quotient, remainder, addr_2align_odd;
	u16 reg, stmp, i = 0, idx = 0;
_func_enter_;
	reg = (u16)(addr_off >> 1);
	addr_2align_odd = (u8)(addr_off & 0x1);

	/*read that start at high part: e.g  1,3,5,7,9,...*/
	if (addr_2align_odd) {
		stmp = eeprom_read16(padapter, reg);
		rbuf[idx++] = (u8) ((stmp>>8)&0xff); /*return hogh-part of the short*/
		reg++; sz--;
	}

	quotient = sz >> 1;
	remainder = sz & 0x1;

	for (i = 0; i < quotient; i++) {
		stmp = eeprom_read16(padapter, reg+i);
		rbuf[idx++] = (u8) (stmp&0xff);
		rbuf[idx++] = (u8) ((stmp>>8)&0xff);
	}

	reg = reg+i;
	if (remainder) { /*end of read at lower part of short : 0,2,4,6,...*/
		stmp = eeprom_read16(padapter, reg);
		rbuf[idx] = (u8)(stmp & 0xff);
	}
_func_exit_;
	return true;
}