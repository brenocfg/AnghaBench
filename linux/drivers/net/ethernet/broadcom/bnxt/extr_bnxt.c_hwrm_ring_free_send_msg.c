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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct hwrm_ring_free_output {int /*<<< orphan*/  error_code; } ;
struct hwrm_ring_free_input {int /*<<< orphan*/  ring_id; int /*<<< orphan*/  ring_type; int /*<<< orphan*/  member_0; } ;
struct bnxt_ring_struct {int /*<<< orphan*/  fw_ring_id; } ;
struct bnxt {int /*<<< orphan*/  dev; int /*<<< orphan*/  hwrm_cmd_lock; int /*<<< orphan*/  state; struct hwrm_ring_free_output* hwrm_cmd_resp_addr; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_STATE_FW_FATAL_COND ; 
 int EIO ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_RING_FREE ; 
 int _hwrm_send_message (struct bnxt*,struct hwrm_ring_free_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_ring_free_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hwrm_ring_free_send_msg(struct bnxt *bp,
				   struct bnxt_ring_struct *ring,
				   u32 ring_type, int cmpl_ring_id)
{
	int rc;
	struct hwrm_ring_free_input req = {0};
	struct hwrm_ring_free_output *resp = bp->hwrm_cmd_resp_addr;
	u16 error_code;

	if (test_bit(BNXT_STATE_FW_FATAL_COND, &bp->state))
		return 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_RING_FREE, cmpl_ring_id, -1);
	req.ring_type = ring_type;
	req.ring_id = cpu_to_le16(ring->fw_ring_id);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	error_code = le16_to_cpu(resp->error_code);
	mutex_unlock(&bp->hwrm_cmd_lock);

	if (rc || error_code) {
		netdev_err(bp->dev, "hwrm_ring_free type %d failed. rc:%x err:%x\n",
			   ring_type, rc, error_code);
		return -EIO;
	}
	return 0;
}