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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  conf; } ;
struct ucsi_dp {int initialized; TYPE_2__* con; int /*<<< orphan*/  work; int /*<<< orphan*/  header; TYPE_1__ data; int /*<<< orphan*/  override; } ;
struct typec_altmode {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
#define  CMDT_INIT 130 
 int /*<<< orphan*/  CMDT_RSP_ACK ; 
 int /*<<< orphan*/  CMDT_RSP_NAK ; 
#define  DP_CMD_CONFIGURE 129 
#define  DP_CMD_STATUS_UPDATE 128 
 int EOPNOTSUPP ; 
 int PD_VDO_CMD (int /*<<< orphan*/ ) ; 
 int PD_VDO_CMDT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_TYPEC_DP_MODE ; 
 int /*<<< orphan*/  USB_TYPEC_DP_SID ; 
 int /*<<< orphan*/  VDO (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  VDO_CMDT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VDO_OPOS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct ucsi_dp* typec_altmode_get_drvdata (struct typec_altmode*) ; 
 struct typec_altmode* typec_altmode_get_partner (struct typec_altmode*) ; 
 int /*<<< orphan*/  ucsi_altmode_update_active (TYPE_2__*) ; 
 int /*<<< orphan*/  ucsi_displayport_configure (struct ucsi_dp*) ; 
 int /*<<< orphan*/  ucsi_displayport_status_update (struct ucsi_dp*) ; 

__attribute__((used)) static int ucsi_displayport_vdm(struct typec_altmode *alt,
				u32 header, const u32 *data, int count)
{
	struct ucsi_dp *dp = typec_altmode_get_drvdata(alt);
	int cmd_type = PD_VDO_CMDT(header);
	int cmd = PD_VDO_CMD(header);

	mutex_lock(&dp->con->lock);

	if (!dp->override && dp->initialized) {
		const struct typec_altmode *p = typec_altmode_get_partner(alt);

		dev_warn(&p->dev,
			 "firmware doesn't support alternate mode overriding\n");
		mutex_unlock(&dp->con->lock);
		return -EOPNOTSUPP;
	}

	switch (cmd_type) {
	case CMDT_INIT:
		dp->header = VDO(USB_TYPEC_DP_SID, 1, cmd);
		dp->header |= VDO_OPOS(USB_TYPEC_DP_MODE);

		switch (cmd) {
		case DP_CMD_STATUS_UPDATE:
			if (ucsi_displayport_status_update(dp))
				dp->header |= VDO_CMDT(CMDT_RSP_NAK);
			else
				dp->header |= VDO_CMDT(CMDT_RSP_ACK);
			break;
		case DP_CMD_CONFIGURE:
			dp->data.conf = *data;
			if (ucsi_displayport_configure(dp)) {
				dp->header |= VDO_CMDT(CMDT_RSP_NAK);
			} else {
				dp->header |= VDO_CMDT(CMDT_RSP_ACK);
				if (dp->initialized)
					ucsi_altmode_update_active(dp->con);
				else
					dp->initialized = true;
			}
			break;
		default:
			dp->header |= VDO_CMDT(CMDT_RSP_ACK);
			break;
		}

		schedule_work(&dp->work);
		break;
	default:
		break;
	}

	mutex_unlock(&dp->con->lock);

	return 0;
}