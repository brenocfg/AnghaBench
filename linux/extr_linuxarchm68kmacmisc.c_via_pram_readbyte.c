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
typedef  int __u8 ;

/* Variables and functions */
 int VIA1B_vRTCClk ; 
 int VIA1B_vRTCData ; 
 size_t vBufB ; 
 size_t vDirB ; 
 int* via1 ; 

__attribute__((used)) static __u8 via_pram_readbyte(void)
{
	int i, reg;
	__u8 data;

	reg = via1[vBufB] & ~VIA1B_vRTCClk;

	/* Set the RTC data line to be an input. */

	via1[vDirB] &= ~VIA1B_vRTCData;

	/* The bits of the byte come out in MSB order */

	data = 0;
	for (i = 0 ; i < 8 ; i++) {
		via1[vBufB] = reg;
		via1[vBufB] = reg | VIA1B_vRTCClk;
		data = (data << 1) | (via1[vBufB] & VIA1B_vRTCData);
	}

	/* Return RTC data line to output state */

	via1[vDirB] |= VIA1B_vRTCData;

	return data;
}