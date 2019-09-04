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

/* Variables and functions */
 int CRC_CCIT_MASK ; 

__attribute__((used)) static u16 nxt200x_crc(u16 crc, u8 c)
{
	u8 i;
	u16 input = (u16) c & 0xFF;

	input<<=8;
	for(i=0; i<8; i++) {
		if((crc^input) & 0x8000)
			crc=(crc<<1)^CRC_CCIT_MASK;
		else
			crc<<=1;
		input<<=1;
	}
	return crc;
}