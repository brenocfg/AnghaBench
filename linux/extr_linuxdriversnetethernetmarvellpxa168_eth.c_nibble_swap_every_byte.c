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

/* Variables and functions */
 int ETH_ALEN ; 

__attribute__((used)) static void nibble_swap_every_byte(unsigned char *mac_addr)
{
	int i;
	for (i = 0; i < ETH_ALEN; i++) {
		mac_addr[i] = ((mac_addr[i] & 0x0f) << 4) |
				((mac_addr[i] & 0xf0) >> 4);
	}
}