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
struct creq_destroy_ah_resp {int dummy; } ;
struct cmdq_destroy_ah {int /*<<< orphan*/  ah_cid; } ;
struct bnxt_qplib_res {struct bnxt_qplib_rcfw* rcfw; } ;
struct bnxt_qplib_rcfw {int dummy; } ;
struct bnxt_qplib_ah {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESTROY_AH ; 
 int /*<<< orphan*/  RCFW_CMD_PREP (struct cmdq_destroy_ah,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_qplib_rcfw_send_message (struct bnxt_qplib_rcfw*,void*,void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

void bnxt_qplib_destroy_ah(struct bnxt_qplib_res *res, struct bnxt_qplib_ah *ah,
			   bool block)
{
	struct bnxt_qplib_rcfw *rcfw = res->rcfw;
	struct cmdq_destroy_ah req;
	struct creq_destroy_ah_resp resp;
	u16 cmd_flags = 0;

	/* Clean up the AH table in the device */
	RCFW_CMD_PREP(req, DESTROY_AH, cmd_flags);

	req.ah_cid = cpu_to_le32(ah->id);

	bnxt_qplib_rcfw_send_message(rcfw, (void *)&req, (void *)&resp, NULL,
				     block);
}