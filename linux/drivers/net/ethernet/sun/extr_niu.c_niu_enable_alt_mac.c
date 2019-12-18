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
typedef  int u64 ;
struct niu {int flags; } ;

/* Variables and functions */
 unsigned long BMAC_ADDR_CMPEN ; 
 int EINVAL ; 
 int NIU_FLAGS_XMAC ; 
 unsigned long XMAC_ADDR_CMPEN ; 
 int niu_num_alt_addr (struct niu*) ; 
 int nr64_mac (unsigned long) ; 
 int /*<<< orphan*/  nw64_mac (unsigned long,int) ; 

__attribute__((used)) static int niu_enable_alt_mac(struct niu *np, int index, int on)
{
	unsigned long reg;
	u64 val, mask;

	if (index >= niu_num_alt_addr(np))
		return -EINVAL;

	if (np->flags & NIU_FLAGS_XMAC) {
		reg = XMAC_ADDR_CMPEN;
		mask = 1 << index;
	} else {
		reg = BMAC_ADDR_CMPEN;
		mask = 1 << (index + 1);
	}

	val = nr64_mac(reg);
	if (on)
		val |= mask;
	else
		val &= ~mask;
	nw64_mac(reg, val);

	return 0;
}