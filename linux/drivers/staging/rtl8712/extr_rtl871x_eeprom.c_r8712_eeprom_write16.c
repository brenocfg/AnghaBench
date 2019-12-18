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
typedef  int /*<<< orphan*/  u16 ;
struct _adapter {int eeprom_address_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_EWDS_OPCODE ; 
 int /*<<< orphan*/  EEPROM_EWEN_OPCODE ; 
 int /*<<< orphan*/  EEPROM_WRITE_OPCODE ; 
 int EE_9346CR ; 
 int _EECS ; 
 int _EEDI ; 
 int _EEDO ; 
 int _EEM0 ; 
 int _EEM1 ; 
 int _EESK ; 
 int /*<<< orphan*/  eeprom_clean (struct _adapter*) ; 
 int r8712_read8 (struct _adapter*,int) ; 
 int /*<<< orphan*/  r8712_write8 (struct _adapter*,int,int) ; 
 int /*<<< orphan*/  shift_out_bits (struct _adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  standby (struct _adapter*) ; 
 scalar_t__ wait_eeprom_cmd_done (struct _adapter*) ; 

void r8712_eeprom_write16(struct _adapter *padapter, u16 reg, u16 data)
{
	u8 x;
	u8 tmp8_ori, tmp8_new, tmp8_clk_ori, tmp8_clk_new;

	tmp8_ori = r8712_read8(padapter, 0x102502f1);
	tmp8_new = tmp8_ori & 0xf7;
	if (tmp8_ori != tmp8_new)
		r8712_write8(padapter, 0x102502f1, tmp8_new);
	tmp8_clk_ori = r8712_read8(padapter, 0x10250003);
	tmp8_clk_new = tmp8_clk_ori | 0x20;
	if (tmp8_clk_new != tmp8_clk_ori)
		r8712_write8(padapter, 0x10250003, tmp8_clk_new);
	x = r8712_read8(padapter, EE_9346CR);
	x &= ~(_EEDI | _EEDO | _EESK | _EEM0);
	x |= _EEM1 | _EECS;
	r8712_write8(padapter, EE_9346CR, x);
	shift_out_bits(padapter, EEPROM_EWEN_OPCODE, 5);
	if (padapter->eeprom_address_size == 8)	/*CF+ and SDIO*/
		shift_out_bits(padapter, 0, 6);
	else	/* USB */
		shift_out_bits(padapter, 0, 4);
	standby(padapter);
	/* Erase this particular word.  Write the erase opcode and register
	 * number in that order. The opcode is 3bits in length; reg is 6
	 * bits long.
	 */
	standby(padapter);
	/* write the new word to the EEPROM
	 * send the write opcode the EEPORM
	 */
	shift_out_bits(padapter, EEPROM_WRITE_OPCODE, 3);
	/* select which word in the EEPROM that we are writing to. */
	shift_out_bits(padapter, reg, padapter->eeprom_address_size);
	/* write the data to the selected EEPROM word. */
	shift_out_bits(padapter, data, 16);
	if (wait_eeprom_cmd_done(padapter)) {
		standby(padapter);
		shift_out_bits(padapter, EEPROM_EWDS_OPCODE, 5);
		shift_out_bits(padapter, reg, 4);
		eeprom_clean(padapter);
	}
	if (tmp8_clk_new != tmp8_clk_ori)
		r8712_write8(padapter, 0x10250003, tmp8_clk_ori);
	if (tmp8_new != tmp8_ori)
		r8712_write8(padapter, 0x102502f1, tmp8_ori);
}