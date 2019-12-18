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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int FDB_HASH_SIZE ; 
 int get_unaligned (int*) ; 
 int jhash_2words (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxlan_salt ; 

__attribute__((used)) static u32 eth_vni_hash(const unsigned char *addr, __be32 vni)
{
	/* use 1 byte of OUI and 3 bytes of NIC */
	u32 key = get_unaligned((u32 *)(addr + 2));

	return jhash_2words(key, vni, vxlan_salt) & (FDB_HASH_SIZE - 1);
}