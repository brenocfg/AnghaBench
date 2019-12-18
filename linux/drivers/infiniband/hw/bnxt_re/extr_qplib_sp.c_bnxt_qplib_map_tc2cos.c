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
struct creq_map_tc_to_cos_resp {int dummy; } ;
struct cmdq_map_tc_to_cos {void* cos1; void* cos0; } ;
struct bnxt_qplib_res {struct bnxt_qplib_rcfw* rcfw; } ;
struct bnxt_qplib_rcfw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAP_TC_TO_COS ; 
 int /*<<< orphan*/  RCFW_CMD_PREP (struct cmdq_map_tc_to_cos,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bnxt_qplib_rcfw_send_message (struct bnxt_qplib_rcfw*,void*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 

int bnxt_qplib_map_tc2cos(struct bnxt_qplib_res *res, u16 *cids)
{
	struct bnxt_qplib_rcfw *rcfw = res->rcfw;
	struct cmdq_map_tc_to_cos req;
	struct creq_map_tc_to_cos_resp resp;
	u16 cmd_flags = 0;

	RCFW_CMD_PREP(req, MAP_TC_TO_COS, cmd_flags);
	req.cos0 = cpu_to_le16(cids[0]);
	req.cos1 = cpu_to_le16(cids[1]);

	return bnxt_qplib_rcfw_send_message(rcfw, (void *)&req, (void *)&resp,
						NULL, 0);
}