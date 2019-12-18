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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int NI_E_SERIAL_CMD_EEPROM_CS ; 
 int /*<<< orphan*/  NI_E_SERIAL_CMD_REG ; 
 unsigned int NI_E_SERIAL_CMD_SCLK ; 
 unsigned int NI_E_SERIAL_CMD_SDATA ; 
 int NI_E_STATUS_PROMOUT ; 
 int /*<<< orphan*/  NI_E_STATUS_REG ; 
 int ni_readb (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_writeb (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_read_eeprom(struct comedi_device *dev, int addr)
{
	unsigned int cmd = NI_E_SERIAL_CMD_EEPROM_CS;
	int bit;
	int bitstring;

	bitstring = 0x0300 | ((addr & 0x100) << 3) | (addr & 0xff);
	ni_writeb(dev, cmd, NI_E_SERIAL_CMD_REG);
	for (bit = 0x8000; bit; bit >>= 1) {
		if (bit & bitstring)
			cmd |= NI_E_SERIAL_CMD_SDATA;
		else
			cmd &= ~NI_E_SERIAL_CMD_SDATA;

		ni_writeb(dev, cmd, NI_E_SERIAL_CMD_REG);
		ni_writeb(dev, NI_E_SERIAL_CMD_SCLK | cmd, NI_E_SERIAL_CMD_REG);
	}
	cmd = NI_E_SERIAL_CMD_EEPROM_CS;
	bitstring = 0;
	for (bit = 0x80; bit; bit >>= 1) {
		ni_writeb(dev, cmd, NI_E_SERIAL_CMD_REG);
		ni_writeb(dev, NI_E_SERIAL_CMD_SCLK | cmd, NI_E_SERIAL_CMD_REG);
		if (ni_readb(dev, NI_E_STATUS_REG) & NI_E_STATUS_PROMOUT)
			bitstring |= bit;
	}
	ni_writeb(dev, 0, NI_E_SERIAL_CMD_REG);

	return bitstring;
}