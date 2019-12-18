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
typedef  int /*<<< orphan*/  u32 ;
struct hwrm_dbg_ring_info_get_output {int /*<<< orphan*/  consumer_index; int /*<<< orphan*/  producer_index; } ;
struct hwrm_dbg_ring_info_get_input {int /*<<< orphan*/  fw_ring_id; int /*<<< orphan*/  ring_type; int /*<<< orphan*/  member_0; } ;
struct bnxt {int /*<<< orphan*/  hwrm_cmd_lock; struct hwrm_dbg_ring_info_get_output* hwrm_cmd_resp_addr; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_DBG_RING_INFO_GET ; 
 int _hwrm_send_message (struct bnxt*,struct hwrm_dbg_ring_info_get_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_dbg_ring_info_get_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnxt_dbg_hwrm_ring_info_get(struct bnxt *bp, u8 ring_type,
				       u32 ring_id, u32 *prod, u32 *cons)
{
	struct hwrm_dbg_ring_info_get_output *resp = bp->hwrm_cmd_resp_addr;
	struct hwrm_dbg_ring_info_get_input req = {0};
	int rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_DBG_RING_INFO_GET, -1, -1);
	req.ring_type = ring_type;
	req.fw_ring_id = cpu_to_le32(ring_id);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	if (!rc) {
		*prod = le32_to_cpu(resp->producer_index);
		*cons = le32_to_cpu(resp->consumer_index);
	}
	mutex_unlock(&bp->hwrm_cmd_lock);
	return rc;
}