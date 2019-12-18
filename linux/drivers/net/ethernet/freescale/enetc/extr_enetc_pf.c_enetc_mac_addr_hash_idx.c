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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int __swab64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_to_u64 (int /*<<< orphan*/  const*) ; 
 int hweight64 (int) ; 

__attribute__((used)) static int enetc_mac_addr_hash_idx(const u8 *addr)
{
	u64 fold = __swab64(ether_addr_to_u64(addr)) >> 16;
	u64 mask = 0;
	int res = 0;
	int i;

	for (i = 0; i < 8; i++)
		mask |= BIT_ULL(i * 6);

	for (i = 0; i < 6; i++)
		res |= (hweight64(fold & (mask << i)) & 0x1) << i;

	return res;
}