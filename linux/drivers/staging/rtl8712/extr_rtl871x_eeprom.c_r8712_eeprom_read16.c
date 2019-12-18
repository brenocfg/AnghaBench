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
typedef  int u16 ;
struct _adapter {int eeprom_address_size; scalar_t__ surprise_removed; } ;

/* Variables and functions */
 int EEPROM_READ_OPCODE ; 
 int EE_9346CR ; 
 int _EECS ; 
 int _EEDI ; 
 int _EEDO ; 
 int _EEM0 ; 
 int _EEM1 ; 
 int _EESK ; 
 int /*<<< orphan*/  eeprom_clean (struct _adapter*) ; 
 void* r8712_read8 (struct _adapter*,int) ; 
 int /*<<< orphan*/  r8712_write8 (struct _adapter*,int,int) ; 
 int shift_in_bits (struct _adapter*) ; 
 int /*<<< orphan*/  shift_out_bits (struct _adapter*,int,int) ; 

u16 r8712_eeprom_read16(struct _adapter *padapter, u16 reg) /*ReadEEprom*/
{
	u16 x;
	u16 data = 0;
	u8 tmp8_ori, tmp8_new, tmp8_clk_ori, tmp8_clk_new;

	tmp8_ori = r8712_read8(padapter, 0x102502f1);
	tmp8_new = tmp8_ori & 0xf7;
	if (tmp8_ori != tmp8_new)
		r8712_write8(padapter, 0x102502f1, tmp8_new);
	tmp8_clk_ori = r8712_read8(padapter, 0x10250003);
	tmp8_clk_new = tmp8_clk_ori | 0x20;
	if (tmp8_clk_new != tmp8_clk_ori)
		r8712_write8(padapter, 0x10250003, tmp8_clk_new);
	if (padapter->surprise_removed)
		goto out;
	/* select EEPROM, reset bits, set _EECS */
	x = r8712_read8(padapter, EE_9346CR);
	if (padapter->surprise_removed)
		goto out;
	x &= ~(_EEDI | _EEDO | _EESK | _EEM0);
	x |= _EEM1 | _EECS;
	r8712_write8(padapter, EE_9346CR, (unsigned char)x);
	/* write the read opcode and register number in that order
	 * The opcode is 3bits in length, reg is 6 bits long
	 */
	shift_out_bits(padapter, EEPROM_READ_OPCODE, 3);
	shift_out_bits(padapter, reg, padapter->eeprom_address_size);
	/* Now read the data (16 bits) in from the selected EEPROM word */
	data = shift_in_bits(padapter);
	eeprom_clean(padapter);
out:
	if (tmp8_clk_new != tmp8_clk_ori)
		r8712_write8(padapter, 0x10250003, tmp8_clk_ori);
	if (tmp8_new != tmp8_ori)
		r8712_write8(padapter, 0x102502f1, tmp8_ori);
	return data;
}