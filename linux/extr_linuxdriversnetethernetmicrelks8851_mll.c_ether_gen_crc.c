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
 long ethernet_polynomial ; 

__attribute__((used)) static unsigned long ether_gen_crc(int length, u8 *data)
{
	long crc = -1;
	while (--length >= 0) {
		u8 current_octet = *data++;
		int bit;

		for (bit = 0; bit < 8; bit++, current_octet >>= 1) {
			crc = (crc << 1) ^
				((crc < 0) ^ (current_octet & 1) ?
			ethernet_polynomial : 0);
		}
	}
	return (unsigned long)crc;
}