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
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int ether_crc (int /*<<< orphan*/ ,unsigned char const*) ; 

__attribute__((used)) static void slic_set_mcast_bit(u64 *mcmask, unsigned char const *addr)
{
	u64 mask = *mcmask;
	u8 crc;
	/* Get the CRC polynomial for the mac address: we use bits 1-8 (lsb),
	 * bitwise reversed, msb (= lsb bit 0 before bitrev) is automatically
	 * discarded.
	 */
	crc = ether_crc(ETH_ALEN, addr) >> 23;
	 /* we only have space on the SLIC for 64 entries */
	crc &= 0x3F;
	mask |= (u64)1 << crc;
	*mcmask = mask;
}