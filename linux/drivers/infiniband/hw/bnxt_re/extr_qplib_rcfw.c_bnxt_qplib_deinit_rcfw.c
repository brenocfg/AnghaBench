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
struct creq_deinitialize_fw_resp {int dummy; } ;
struct cmdq_deinitialize_fw {int dummy; } ;
struct bnxt_qplib_rcfw {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEINITIALIZE_FW ; 
 int /*<<< orphan*/  FIRMWARE_INITIALIZED_FLAG ; 
 int /*<<< orphan*/  RCFW_CMD_PREP (struct cmdq_deinitialize_fw,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bnxt_qplib_rcfw_send_message (struct bnxt_qplib_rcfw*,void*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int bnxt_qplib_deinit_rcfw(struct bnxt_qplib_rcfw *rcfw)
{
	struct cmdq_deinitialize_fw req;
	struct creq_deinitialize_fw_resp resp;
	u16 cmd_flags = 0;
	int rc;

	RCFW_CMD_PREP(req, DEINITIALIZE_FW, cmd_flags);
	rc = bnxt_qplib_rcfw_send_message(rcfw, (void *)&req, (void *)&resp,
					  NULL, 0);
	if (rc)
		return rc;

	clear_bit(FIRMWARE_INITIALIZED_FLAG, &rcfw->flags);
	return 0;
}