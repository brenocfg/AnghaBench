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
typedef  int /*<<< orphan*/  index ;

/* Variables and functions */
 void* find_node_by_prop_value (int /*<<< orphan*/ *,char*,void*,int) ; 
 int /*<<< orphan*/  printf (char*,int,int const,int const,int const,int const,int const,int const) ; 
 int /*<<< orphan*/  setprop (void*,char*,int const*,int) ; 

void dt_fixup_mac_address(u32 index, const u8 *addr)
{
	void *devp = find_node_by_prop_value(NULL, "linux,network-index",
	                                     (void*)&index, sizeof(index));

	if (devp) {
		printf("ENET%d: local-mac-address <-"
		       " %02x:%02x:%02x:%02x:%02x:%02x\n\r", index,
		       addr[0], addr[1], addr[2],
		       addr[3], addr[4], addr[5]);

		setprop(devp, "local-mac-address", addr, 6);
	}
}