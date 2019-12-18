#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_3__ {scalar_t__ dir; } ;
struct TYPE_4__ {TYPE_1__ l2_key; } ;
struct bnxt_tc_flow_node {int /*<<< orphan*/  flow_handle; TYPE_2__ flow; int /*<<< orphan*/  flow_id; } ;
struct bnxt {int fw_cap; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 scalar_t__ BNXT_DIR_RX ; 
 int BNXT_FW_CAP_OVS_64BIT_HANDLE ; 
 int CFA_FLOW_INFO_REQ_FLOW_HANDLE_DIR_RX ; 
 int CFA_FLOW_INFO_REQ_FLOW_HANDLE_MAX_MASK ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 

__attribute__((used)) static void bnxt_fill_cfa_stats_req(struct bnxt *bp,
				    struct bnxt_tc_flow_node *flow_node,
				    __le16 *flow_handle, __le32 *flow_id)
{
	u16 handle;

	if (bp->fw_cap & BNXT_FW_CAP_OVS_64BIT_HANDLE) {
		*flow_id = flow_node->flow_id;

		/* If flow_id is used to fetch flow stats then:
		 * 1. lower 12 bits of flow_handle must be set to all 1s.
		 * 2. 15th bit of flow_handle must specify the flow
		 *    direction (TX/RX).
		 */
		if (flow_node->flow.l2_key.dir == BNXT_DIR_RX)
			handle = CFA_FLOW_INFO_REQ_FLOW_HANDLE_DIR_RX |
				 CFA_FLOW_INFO_REQ_FLOW_HANDLE_MAX_MASK;
		else
			handle = CFA_FLOW_INFO_REQ_FLOW_HANDLE_MAX_MASK;

		*flow_handle = cpu_to_le16(handle);
	} else {
		*flow_handle = flow_node->flow_handle;
	}
}