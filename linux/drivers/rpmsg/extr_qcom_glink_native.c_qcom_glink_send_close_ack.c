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
struct qcom_glink {int dummy; } ;
struct glink_msg {scalar_t__ param2; void* param1; void* cmd; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 unsigned int RPM_CMD_CLOSE_ACK ; 
 void* cpu_to_le16 (unsigned int) ; 
 int /*<<< orphan*/  qcom_glink_tx (struct qcom_glink*,struct glink_msg*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qcom_glink_send_close_ack(struct qcom_glink *glink,
				      unsigned int rcid)
{
	struct glink_msg req;

	req.cmd = cpu_to_le16(RPM_CMD_CLOSE_ACK);
	req.param1 = cpu_to_le16(rcid);
	req.param2 = 0;

	qcom_glink_tx(glink, &req, sizeof(req), NULL, 0, true);
}