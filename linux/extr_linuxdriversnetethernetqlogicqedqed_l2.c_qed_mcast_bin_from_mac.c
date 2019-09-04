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

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  ETH_MULTICAST_BIN_FROM_MAC_SEED ; 
 int qed_crc32c_le (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

u8 qed_mcast_bin_from_mac(u8 *mac)
{
	u32 crc = qed_crc32c_le(ETH_MULTICAST_BIN_FROM_MAC_SEED,
				mac, ETH_ALEN);

	return crc & 0xff;
}