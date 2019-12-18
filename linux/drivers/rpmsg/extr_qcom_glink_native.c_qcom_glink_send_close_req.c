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
struct glink_channel {int /*<<< orphan*/  lcid; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  RPM_CMD_CLOSE ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_glink_tx (struct qcom_glink*,struct glink_msg*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qcom_glink_send_close_req(struct qcom_glink *glink,
				      struct glink_channel *channel)
{
	struct glink_msg req;

	req.cmd = cpu_to_le16(RPM_CMD_CLOSE);
	req.param1 = cpu_to_le16(channel->lcid);
	req.param2 = 0;

	qcom_glink_tx(glink, &req, sizeof(req), NULL, 0, true);
}