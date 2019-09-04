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
struct hwrm_wol_filter_alloc_output {int /*<<< orphan*/  wol_filter_id; } ;
struct hwrm_wol_filter_alloc_input {int /*<<< orphan*/  mac_address; int /*<<< orphan*/  enables; int /*<<< orphan*/  wol_type; int /*<<< orphan*/  port_id; int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {int /*<<< orphan*/  port_id; } ;
struct bnxt {int /*<<< orphan*/  hwrm_cmd_lock; int /*<<< orphan*/  wol_filter_id; TYPE_2__* dev; TYPE_1__ pf; struct hwrm_wol_filter_alloc_output* hwrm_cmd_resp_addr; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_WOL_FILTER_ALLOC ; 
 int /*<<< orphan*/  WOL_FILTER_ALLOC_REQ_ENABLES_MAC_ADDRESS ; 
 int /*<<< orphan*/  WOL_FILTER_ALLOC_REQ_WOL_TYPE_MAGICPKT ; 
 int _hwrm_send_message (struct bnxt*,struct hwrm_wol_filter_alloc_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_wol_filter_alloc_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int bnxt_hwrm_alloc_wol_fltr(struct bnxt *bp)
{
	struct hwrm_wol_filter_alloc_input req = {0};
	struct hwrm_wol_filter_alloc_output *resp = bp->hwrm_cmd_resp_addr;
	int rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_WOL_FILTER_ALLOC, -1, -1);
	req.port_id = cpu_to_le16(bp->pf.port_id);
	req.wol_type = WOL_FILTER_ALLOC_REQ_WOL_TYPE_MAGICPKT;
	req.enables = cpu_to_le32(WOL_FILTER_ALLOC_REQ_ENABLES_MAC_ADDRESS);
	memcpy(req.mac_address, bp->dev->dev_addr, ETH_ALEN);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	if (!rc)
		bp->wol_filter_id = resp->wol_filter_id;
	mutex_unlock(&bp->hwrm_cmd_lock);
	return rc;
}