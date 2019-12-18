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

/* Variables and functions */
 int spi_write (struct spi_device*,int*,int) ; 

__attribute__((used)) static int ad5624r_spi_write(struct spi_device *spi,
			     u8 cmd, u8 addr, u16 val, u8 shift)
{
	u32 data;
	u8 msg[3];

	/*
	 * The input shift register is 24 bits wide. The first two bits are
	 * don't care bits. The next three are the command bits, C2 to C0,
	 * followed by the 3-bit DAC address, A2 to A0, and then the
	 * 16-, 14-, 12-bit data-word. The data-word comprises the 16-,
	 * 14-, 12-bit input code followed by 0, 2, or 4 don't care bits,
	 * for the AD5664R, AD5644R, and AD5624R, respectively.
	 */
	data = (0 << 22) | (cmd << 19) | (addr << 16) | (val << shift);
	msg[0] = data >> 16;
	msg[1] = data >> 8;
	msg[2] = data;

	return spi_write(spi, msg, 3);
}