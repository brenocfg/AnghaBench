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
struct spi_device {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int spi_write (struct spi_device*,int*,int) ; 

__attribute__((used)) static int ltc2632_spi_write(struct spi_device *spi,
			     u8 cmd, u8 addr, u16 val, u8 shift)
{
	u32 data;
	u8 msg[3];

	/*
	 * The input shift register is 24 bits wide.
	 * The next four are the command bits, C3 to C0,
	 * followed by the 4-bit DAC address, A3 to A0, and then the
	 * 12-, 10-, 8-bit data-word. The data-word comprises the 12-,
	 * 10-, 8-bit input code followed by 4, 6, or 8 don't care bits.
	 */
	data = (cmd << 20) | (addr << 16) | (val << shift);
	msg[0] = data >> 16;
	msg[1] = data >> 8;
	msg[2] = data;

	return spi_write(spi, msg, sizeof(msg));
}