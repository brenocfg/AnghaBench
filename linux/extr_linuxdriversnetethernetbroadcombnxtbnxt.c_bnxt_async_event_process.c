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
typedef  int u32 ;
typedef  int u16 ;
struct hwrm_async_event_cmpl {int /*<<< orphan*/  event_data1; int /*<<< orphan*/  event_id; } ;
struct bnxt_link_info {int autoneg; int force_link_speed; } ;
struct TYPE_2__ {int port_id; } ;
struct bnxt {int /*<<< orphan*/  sp_event; TYPE_1__ pf; int /*<<< orphan*/  dev; struct bnxt_link_info link_info; } ;

/* Variables and functions */
#define  ASYNC_EVENT_CMPL_EVENT_ID_LINK_SPEED_CFG_CHANGE 132 
#define  ASYNC_EVENT_CMPL_EVENT_ID_LINK_STATUS_CHANGE 131 
#define  ASYNC_EVENT_CMPL_EVENT_ID_PF_DRVR_UNLOAD 130 
#define  ASYNC_EVENT_CMPL_EVENT_ID_PORT_CONN_NOT_ALLOWED 129 
#define  ASYNC_EVENT_CMPL_EVENT_ID_VF_CFG_CHANGE 128 
 int BNXT_AUTONEG_SPEED ; 
 int BNXT_GET_EVENT_PORT (int) ; 
 int /*<<< orphan*/  BNXT_HWRM_PF_UNLOAD_SP_EVENT ; 
 int /*<<< orphan*/  BNXT_HWRM_PORT_MODULE_SP_EVENT ; 
 int /*<<< orphan*/  BNXT_LINK_CHNG_SP_EVENT ; 
 int /*<<< orphan*/  BNXT_LINK_SPEED_CHNG_SP_EVENT ; 
 int /*<<< orphan*/  BNXT_PF (struct bnxt*) ; 
 int /*<<< orphan*/  BNXT_RESET_TASK_SILENT_SP_EVENT ; 
 int /*<<< orphan*/  BNXT_VF (struct bnxt*) ; 
 int SPEED_UNKNOWN ; 
 int bnxt_fw_to_ethtool_speed (int) ; 
 int /*<<< orphan*/  bnxt_queue_sp_work (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_ulp_async_events (struct bnxt*,struct hwrm_async_event_cmpl*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnxt_async_event_process(struct bnxt *bp,
				    struct hwrm_async_event_cmpl *cmpl)
{
	u16 event_id = le16_to_cpu(cmpl->event_id);

	/* TODO CHIMP_FW: Define event id's for link change, error etc */
	switch (event_id) {
	case ASYNC_EVENT_CMPL_EVENT_ID_LINK_SPEED_CFG_CHANGE: {
		u32 data1 = le32_to_cpu(cmpl->event_data1);
		struct bnxt_link_info *link_info = &bp->link_info;

		if (BNXT_VF(bp))
			goto async_event_process_exit;

		/* print unsupported speed warning in forced speed mode only */
		if (!(link_info->autoneg & BNXT_AUTONEG_SPEED) &&
		    (data1 & 0x20000)) {
			u16 fw_speed = link_info->force_link_speed;
			u32 speed = bnxt_fw_to_ethtool_speed(fw_speed);

			if (speed != SPEED_UNKNOWN)
				netdev_warn(bp->dev, "Link speed %d no longer supported\n",
					    speed);
		}
		set_bit(BNXT_LINK_SPEED_CHNG_SP_EVENT, &bp->sp_event);
	}
	/* fall through */
	case ASYNC_EVENT_CMPL_EVENT_ID_LINK_STATUS_CHANGE:
		set_bit(BNXT_LINK_CHNG_SP_EVENT, &bp->sp_event);
		break;
	case ASYNC_EVENT_CMPL_EVENT_ID_PF_DRVR_UNLOAD:
		set_bit(BNXT_HWRM_PF_UNLOAD_SP_EVENT, &bp->sp_event);
		break;
	case ASYNC_EVENT_CMPL_EVENT_ID_PORT_CONN_NOT_ALLOWED: {
		u32 data1 = le32_to_cpu(cmpl->event_data1);
		u16 port_id = BNXT_GET_EVENT_PORT(data1);

		if (BNXT_VF(bp))
			break;

		if (bp->pf.port_id != port_id)
			break;

		set_bit(BNXT_HWRM_PORT_MODULE_SP_EVENT, &bp->sp_event);
		break;
	}
	case ASYNC_EVENT_CMPL_EVENT_ID_VF_CFG_CHANGE:
		if (BNXT_PF(bp))
			goto async_event_process_exit;
		set_bit(BNXT_RESET_TASK_SILENT_SP_EVENT, &bp->sp_event);
		break;
	default:
		goto async_event_process_exit;
	}
	bnxt_queue_sp_work(bp);
async_event_process_exit:
	bnxt_ulp_async_events(bp, cmpl);
	return 0;
}