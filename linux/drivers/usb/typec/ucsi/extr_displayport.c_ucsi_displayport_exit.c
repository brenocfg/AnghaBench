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
struct ucsi_dp {int vdo_size; TYPE_1__* con; int /*<<< orphan*/  work; int /*<<< orphan*/ * vdo_data; int /*<<< orphan*/  header; int /*<<< orphan*/  offset; int /*<<< orphan*/  override; } ;
struct ucsi_control {int /*<<< orphan*/  raw_cmd; } ;
struct typec_altmode {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  ucsi; int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMDT_RSP_ACK ; 
 int /*<<< orphan*/  CMD_EXIT_MODE ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  UCSI_CMD_SET_NEW_CAM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_TYPEC_DP_MODE ; 
 int /*<<< orphan*/  USB_TYPEC_DP_SID ; 
 int /*<<< orphan*/  VDO (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VDO_CMDT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VDO_OPOS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct ucsi_dp* typec_altmode_get_drvdata (struct typec_altmode*) ; 
 struct typec_altmode* typec_altmode_get_partner (struct typec_altmode*) ; 
 int ucsi_send_command (int /*<<< orphan*/ ,struct ucsi_control*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ucsi_displayport_exit(struct typec_altmode *alt)
{
	struct ucsi_dp *dp = typec_altmode_get_drvdata(alt);
	struct ucsi_control ctrl;
	int ret = 0;

	mutex_lock(&dp->con->lock);

	if (!dp->override) {
		const struct typec_altmode *p = typec_altmode_get_partner(alt);

		dev_warn(&p->dev,
			 "firmware doesn't support alternate mode overriding\n");
		ret = -EOPNOTSUPP;
		goto out_unlock;
	}

	ctrl.raw_cmd = UCSI_CMD_SET_NEW_CAM(dp->con->num, 0, dp->offset, 0);
	ret = ucsi_send_command(dp->con->ucsi, &ctrl, NULL, 0);
	if (ret < 0)
		goto out_unlock;

	dp->header = VDO(USB_TYPEC_DP_SID, 1, CMD_EXIT_MODE);
	dp->header |= VDO_OPOS(USB_TYPEC_DP_MODE);
	dp->header |= VDO_CMDT(CMDT_RSP_ACK);

	dp->vdo_data = NULL;
	dp->vdo_size = 1;

	schedule_work(&dp->work);

out_unlock:
	mutex_unlock(&dp->con->lock);

	return ret;
}