#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct ucsi_dp {int vdo_size; TYPE_3__* con; int /*<<< orphan*/  work; int /*<<< orphan*/ * vdo_data; int /*<<< orphan*/  header; scalar_t__ initialized; int /*<<< orphan*/  override; } ;
struct ucsi_control {int dummy; } ;
struct typec_altmode {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  cur ;
struct TYPE_8__ {TYPE_2__* ppm; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; struct typec_altmode** port_altmode; TYPE_4__* ucsi; int /*<<< orphan*/  num; } ;
struct TYPE_6__ {TYPE_1__* data; } ;
struct TYPE_5__ {int version; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMDT_RSP_ACK ; 
 int /*<<< orphan*/  CMD_ENTER_MODE ; 
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  UCSI_CMD_GET_CURRENT_CAM (struct ucsi_control,int /*<<< orphan*/ ) ; 
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
 int ucsi_send_command (TYPE_4__*,struct ucsi_control*,int*,int) ; 

__attribute__((used)) static int ucsi_displayport_enter(struct typec_altmode *alt)
{
	struct ucsi_dp *dp = typec_altmode_get_drvdata(alt);
	struct ucsi_control ctrl;
	u8 cur = 0;
	int ret;

	mutex_lock(&dp->con->lock);

	if (!dp->override && dp->initialized) {
		const struct typec_altmode *p = typec_altmode_get_partner(alt);

		dev_warn(&p->dev,
			 "firmware doesn't support alternate mode overriding\n");
		mutex_unlock(&dp->con->lock);
		return -EOPNOTSUPP;
	}

	UCSI_CMD_GET_CURRENT_CAM(ctrl, dp->con->num);
	ret = ucsi_send_command(dp->con->ucsi, &ctrl, &cur, sizeof(cur));
	if (ret < 0) {
		if (dp->con->ucsi->ppm->data->version > 0x0100) {
			mutex_unlock(&dp->con->lock);
			return ret;
		}
		cur = 0xff;
	}

	if (cur != 0xff) {
		mutex_unlock(&dp->con->lock);
		if (dp->con->port_altmode[cur] == alt)
			return 0;
		return -EBUSY;
	}

	/*
	 * We can't send the New CAM command yet to the PPM as it needs the
	 * configuration value as well. Pretending that we have now entered the
	 * mode, and letting the alt mode driver continue.
	 */

	dp->header = VDO(USB_TYPEC_DP_SID, 1, CMD_ENTER_MODE);
	dp->header |= VDO_OPOS(USB_TYPEC_DP_MODE);
	dp->header |= VDO_CMDT(CMDT_RSP_ACK);

	dp->vdo_data = NULL;
	dp->vdo_size = 1;

	schedule_work(&dp->work);

	mutex_unlock(&dp->con->lock);

	return 0;
}