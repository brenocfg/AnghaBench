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
typedef  unsigned char u8 ;
typedef  int u32 ;
struct hclge_mac_vlan_tbl_entry_cmd {int /*<<< orphan*/  mac_addr_lo16; int /*<<< orphan*/  mac_addr_hi32; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static void hclge_prepare_mac_addr(struct hclge_mac_vlan_tbl_entry_cmd *new_req,
				   const u8 *addr)
{
	const unsigned char *mac_addr = addr;
	u32 high_val = mac_addr[2] << 16 | (mac_addr[3] << 24) |
		       (mac_addr[0]) | (mac_addr[1] << 8);
	u32 low_val  = mac_addr[4] | (mac_addr[5] << 8);

	new_req->mac_addr_hi32 = cpu_to_le32(high_val);
	new_req->mac_addr_lo16 = cpu_to_le16(low_val & 0xffff);
}