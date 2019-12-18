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
typedef  int /*<<< orphan*/  u16 ;
struct hwrm_port_phy_qcaps_output {int /*<<< orphan*/  supported_speeds_force_mode; } ;
struct hwrm_port_phy_qcaps_input {int /*<<< orphan*/  member_0; } ;
struct bnxt {int /*<<< orphan*/  hwrm_cmd_lock; struct hwrm_port_phy_qcaps_output* hwrm_cmd_resp_addr; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_QCAPS ; 
 int _hwrm_send_message (struct bnxt*,struct hwrm_port_phy_qcaps_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_port_phy_qcaps_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnxt_query_force_speeds(struct bnxt *bp, u16 *force_speeds)
{
	struct hwrm_port_phy_qcaps_output *resp = bp->hwrm_cmd_resp_addr;
	struct hwrm_port_phy_qcaps_input req = {0};
	int rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_PORT_PHY_QCAPS, -1, -1);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	if (!rc)
		*force_speeds = le16_to_cpu(resp->supported_speeds_force_mode);

	mutex_unlock(&bp->hwrm_cmd_lock);
	return rc;
}