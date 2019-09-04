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
typedef  unsigned long long u64 ;
typedef  scalar_t__ u32 ;
struct netxen_adapter {int portnum; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 scalar_t__ NX_FW_MAC_ADDR_OFFSET ; 
 scalar_t__ NX_OLD_MAC_ADDR_OFFSET ; 
 int netxen_get_flash_block (struct netxen_adapter*,scalar_t__,int,int /*<<< orphan*/ *) ; 

int netxen_get_flash_mac_addr(struct netxen_adapter *adapter, u64 *mac)
{
	__le32 *pmac = (__le32 *) mac;
	u32 offset;

	offset = NX_FW_MAC_ADDR_OFFSET + (adapter->portnum * sizeof(u64));

	if (netxen_get_flash_block(adapter, offset, sizeof(u64), pmac) == -1)
		return -1;

	if (*mac == ~0ULL) {

		offset = NX_OLD_MAC_ADDR_OFFSET +
			(adapter->portnum * sizeof(u64));

		if (netxen_get_flash_block(adapter,
					offset, sizeof(u64), pmac) == -1)
			return -1;

		if (*mac == ~0ULL)
			return -1;
	}
	return 0;
}