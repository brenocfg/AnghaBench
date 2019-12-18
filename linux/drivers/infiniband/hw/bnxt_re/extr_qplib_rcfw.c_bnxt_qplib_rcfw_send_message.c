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
typedef  int u8 ;
typedef  int u16 ;
struct creq_qp_event {scalar_t__ status; } ;
struct creq_base {int dummy; } ;
struct cmdq_base {int opcode; int /*<<< orphan*/  cookie; } ;
struct bnxt_qplib_rcfw {TYPE_1__* pdev; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EFAULT ; 
 int /*<<< orphan*/  FIRMWARE_TIMED_OUT ; 
 scalar_t__ RCFW_CMD_WAIT_TIME_MS ; 
 int RCFW_MAX_COOKIE_VALUE ; 
 int __block_for_resp (struct bnxt_qplib_rcfw*,int) ; 
 int __send_message (struct bnxt_qplib_rcfw*,struct cmdq_base*,struct creq_base*,void*,int) ; 
 int __wait_for_resp (struct bnxt_qplib_rcfw*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int,...) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int bnxt_qplib_rcfw_send_message(struct bnxt_qplib_rcfw *rcfw,
				 struct cmdq_base *req,
				 struct creq_base *resp,
				 void *sb, u8 is_block)
{
	struct creq_qp_event *evnt = (struct creq_qp_event *)resp;
	u16 cookie;
	u8 opcode, retry_cnt = 0xFF;
	int rc = 0;

	do {
		opcode = req->opcode;
		rc = __send_message(rcfw, req, resp, sb, is_block);
		cookie = le16_to_cpu(req->cookie) & RCFW_MAX_COOKIE_VALUE;
		if (!rc)
			break;

		if (!retry_cnt || (rc != -EAGAIN && rc != -EBUSY)) {
			/* send failed */
			dev_err(&rcfw->pdev->dev, "cmdq[%#x]=%#x send failed\n",
				cookie, opcode);
			return rc;
		}
		is_block ? mdelay(1) : usleep_range(500, 1000);

	} while (retry_cnt--);

	if (is_block)
		rc = __block_for_resp(rcfw, cookie);
	else
		rc = __wait_for_resp(rcfw, cookie);
	if (rc) {
		/* timed out */
		dev_err(&rcfw->pdev->dev, "cmdq[%#x]=%#x timedout (%d)msec\n",
			cookie, opcode, RCFW_CMD_WAIT_TIME_MS);
		set_bit(FIRMWARE_TIMED_OUT, &rcfw->flags);
		return rc;
	}

	if (evnt->status) {
		/* failed with status */
		dev_err(&rcfw->pdev->dev, "cmdq[%#x]=%#x status %#x\n",
			cookie, opcode, evnt->status);
		rc = -EFAULT;
	}

	return rc;
}