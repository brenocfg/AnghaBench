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
 int* via1 ; 

__attribute__((used)) static void via_pram_writebyte(__u8 data)
{
	int i, reg, bit;

	reg = via1[vBufB] & ~(VIA1B_vRTCClk | VIA1B_vRTCData);

	/* The bits of the byte go in in MSB order */

	for (i = 0 ; i < 8 ; i++) {
		bit = data & 0x80? 1 : 0;
		data <<= 1;
		via1[vBufB] = reg | bit;
		via1[vBufB] = reg | bit | VIA1B_vRTCClk;
	}
}