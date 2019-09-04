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
struct ql_adapter {int dummy; } ;

/* Variables and functions */
 int MAC_ADDR_ADR ; 
 int /*<<< orphan*/  MAC_ADDR_DATA ; 
 int /*<<< orphan*/  MAC_ADDR_IDX ; 
 int MAC_ADDR_IDX_SHIFT ; 
 int MAC_ADDR_MAX_CAM_ENTRIES ; 
 int MAC_ADDR_MAX_CAM_WCOUNT ; 
 int MAC_ADDR_MAX_FC_MAC_ENTRIES ; 
 int MAC_ADDR_MAX_FC_MAC_WCOUNT ; 
 int MAC_ADDR_MAX_MGMT_MAC_ENTRIES ; 
 int MAC_ADDR_MAX_MGMT_MAC_WCOUNT ; 
 int MAC_ADDR_MAX_MGMT_TU_DP_ENTRIES ; 
 int MAC_ADDR_MAX_MGMT_TU_DP_WCOUNT ; 
 int MAC_ADDR_MAX_MGMT_V4_ENTRIES ; 
 int MAC_ADDR_MAX_MGMT_V4_WCOUNT ; 
 int MAC_ADDR_MAX_MGMT_V6_ENTRIES ; 
 int MAC_ADDR_MAX_MGMT_V6_WCOUNT ; 
 int MAC_ADDR_MAX_MGMT_VLAN_ENTRIES ; 
 int MAC_ADDR_MAX_MGMT_VLAN_WCOUNT ; 
 int MAC_ADDR_MR ; 
 int MAC_ADDR_RS ; 
 int MAC_ADDR_TYPE_COUNT ; 
 int MAC_ADDR_TYPE_SHIFT ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int ql_read32 (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_write32 (struct ql_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ql_get_mac_protocol_registers(struct ql_adapter *qdev, u32 *buf)
{
	u32 result_index, result_data;
	u32 type;
	u32 index;
	u32 offset;
	u32 val;
	u32 initial_val = MAC_ADDR_RS;
	u32 max_index;
	u32 max_offset;

	for (type = 0; type < MAC_ADDR_TYPE_COUNT; type++) {
		switch (type) {

		case 0: /* CAM */
			initial_val |= MAC_ADDR_ADR;
			max_index = MAC_ADDR_MAX_CAM_ENTRIES;
			max_offset = MAC_ADDR_MAX_CAM_WCOUNT;
			break;
		case 1: /* Multicast MAC Address */
			max_index = MAC_ADDR_MAX_CAM_WCOUNT;
			max_offset = MAC_ADDR_MAX_CAM_WCOUNT;
			break;
		case 2: /* VLAN filter mask */
		case 3: /* MC filter mask */
			max_index = MAC_ADDR_MAX_CAM_WCOUNT;
			max_offset = MAC_ADDR_MAX_CAM_WCOUNT;
			break;
		case 4: /* FC MAC addresses */
			max_index = MAC_ADDR_MAX_FC_MAC_ENTRIES;
			max_offset = MAC_ADDR_MAX_FC_MAC_WCOUNT;
			break;
		case 5: /* Mgmt MAC addresses */
			max_index = MAC_ADDR_MAX_MGMT_MAC_ENTRIES;
			max_offset = MAC_ADDR_MAX_MGMT_MAC_WCOUNT;
			break;
		case 6: /* Mgmt VLAN addresses */
			max_index = MAC_ADDR_MAX_MGMT_VLAN_ENTRIES;
			max_offset = MAC_ADDR_MAX_MGMT_VLAN_WCOUNT;
			break;
		case 7: /* Mgmt IPv4 address */
			max_index = MAC_ADDR_MAX_MGMT_V4_ENTRIES;
			max_offset = MAC_ADDR_MAX_MGMT_V4_WCOUNT;
			break;
		case 8: /* Mgmt IPv6 address */
			max_index = MAC_ADDR_MAX_MGMT_V6_ENTRIES;
			max_offset = MAC_ADDR_MAX_MGMT_V6_WCOUNT;
			break;
		case 9: /* Mgmt TCP/UDP Dest port */
			max_index = MAC_ADDR_MAX_MGMT_TU_DP_ENTRIES;
			max_offset = MAC_ADDR_MAX_MGMT_TU_DP_WCOUNT;
			break;
		default:
			pr_err("Bad type!!! 0x%08x\n", type);
			max_index = 0;
			max_offset = 0;
			break;
		}
		for (index = 0; index < max_index; index++) {
			for (offset = 0; offset < max_offset; offset++) {
				val = initial_val
					| (type << MAC_ADDR_TYPE_SHIFT)
					| (index << MAC_ADDR_IDX_SHIFT)
					| (offset);
				ql_write32(qdev, MAC_ADDR_IDX, val);
				result_index = 0;
				while ((result_index & MAC_ADDR_MR) == 0) {
					result_index = ql_read32(qdev,
								MAC_ADDR_IDX);
				}
				result_data = ql_read32(qdev, MAC_ADDR_DATA);
				*buf = result_index;
				buf++;
				*buf = result_data;
				buf++;
			}
		}
	}
}