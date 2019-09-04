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
typedef  int u32 ;
struct ipoib_neigh_hash {int mask; } ;

/* Variables and functions */
 int IPOIB_QPN_MASK ; 
 int jhash_3words (int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 ipoib_addr_hash(struct ipoib_neigh_hash *htbl, u8 *daddr)
{
	/*
	 * Use only the address parts that contributes to spreading
	 * The subnet prefix is not used as one can not connect to
	 * same remote port (GUID) using the same remote QPN via two
	 * different subnets.
	 */
	 /* qpn octets[1:4) & port GUID octets[12:20) */
	u32 *d32 = (u32 *) daddr;
	u32 hv;

	hv = jhash_3words(d32[3], d32[4], IPOIB_QPN_MASK & d32[0], 0);
	return hv & htbl->mask;
}