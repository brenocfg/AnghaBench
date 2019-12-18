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

/* Variables and functions */
 int BIT (int) ; 
 int CR_INIT_REENUMERATE ; 
 int CR_NEXT_REENUMERATE ; 
 int CR_SET_BRIGHTNESS ; 

__attribute__((used)) static void cr0014114_calc_crc(u8 *buf, const size_t len)
{
	size_t	i;
	u8	crc;

	for (i = 1, crc = 1; i < len - 1; i++)
		crc += buf[i];
	crc |= BIT(7);

	/* special case when CRC matches the SPI commands */
	if (crc == CR_SET_BRIGHTNESS ||
	    crc == CR_INIT_REENUMERATE ||
	    crc == CR_NEXT_REENUMERATE)
		crc = 0xfe;

	buf[len - 1] = crc;
}