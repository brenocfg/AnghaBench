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
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int ether_crc_le (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void am79c961_mc_hash(char *addr, u16 *hash)
{
	int idx, bit;
	u32 crc;

	crc = ether_crc_le(ETH_ALEN, addr);

	idx = crc >> 30;
	bit = (crc >> 26) & 15;

	hash[idx] |= 1 << bit;
}