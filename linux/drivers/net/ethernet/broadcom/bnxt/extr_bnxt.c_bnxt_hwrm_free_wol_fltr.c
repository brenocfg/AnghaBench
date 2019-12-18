#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hwrm_wol_filter_free_input {int /*<<< orphan*/  wol_filter_id; int /*<<< orphan*/  enables; int /*<<< orphan*/  port_id; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  port_id; } ;
struct bnxt {int /*<<< orphan*/  wol_filter_id; TYPE_1__ pf; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_WOL_FILTER_FREE ; 
 int /*<<< orphan*/  WOL_FILTER_FREE_REQ_ENABLES_WOL_FILTER_ID ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_wol_filter_free_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_wol_filter_free_input*,int,int /*<<< orphan*/ ) ; 

int bnxt_hwrm_free_wol_fltr(struct bnxt *bp)
{
	struct hwrm_wol_filter_free_input req = {0};
	int rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_WOL_FILTER_FREE, -1, -1);
	req.port_id = cpu_to_le16(bp->pf.port_id);
	req.enables = cpu_to_le32(WOL_FILTER_FREE_REQ_ENABLES_WOL_FILTER_ID);
	req.wol_filter_id = bp->wol_filter_id;
	rc = hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	return rc;
}