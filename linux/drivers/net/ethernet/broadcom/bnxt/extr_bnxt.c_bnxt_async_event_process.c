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
struct hwrm_async_event_cmpl {int /*<<< orphan*/  event_data1; int /*<<< orphan*/  timestamp_hi; int /*<<< orphan*/  timestamp_lo; int /*<<< orphan*/  event_id; } ;
struct bnxt_link_info {int autoneg; int force_link_speed; } ;
struct bnxt_fw_health {int polling_dsecs; void* last_fw_reset_cnt; void* last_fw_heartbeat; int /*<<< orphan*/  tmr_multiplier; int /*<<< orphan*/  tmr_counter; int /*<<< orphan*/  master; int /*<<< orphan*/  enabled; } ;
struct TYPE_2__ {int port_id; } ;
struct bnxt {int fw_reset_max_dsecs; int current_interval; int /*<<< orphan*/  dev; struct bnxt_fw_health* fw_health; int /*<<< orphan*/  sp_event; int /*<<< orphan*/  state; int /*<<< orphan*/  fw_reset_min_dsecs; int /*<<< orphan*/  fw_reset_timestamp; TYPE_1__ pf; struct bnxt_link_info link_info; } ;

/* Variables and functions */
#define  ASYNC_EVENT_CMPL_EVENT_ID_ERROR_RECOVERY 134 
#define  ASYNC_EVENT_CMPL_EVENT_ID_LINK_SPEED_CFG_CHANGE 133 
#define  ASYNC_EVENT_CMPL_EVENT_ID_LINK_STATUS_CHANGE 132 
#define  ASYNC_EVENT_CMPL_EVENT_ID_PF_DRVR_UNLOAD 131 
#define  ASYNC_EVENT_CMPL_EVENT_ID_PORT_CONN_NOT_ALLOWED 130 
#define  ASYNC_EVENT_CMPL_EVENT_ID_RESET_NOTIFY 129 
#define  ASYNC_EVENT_CMPL_EVENT_ID_VF_CFG_CHANGE 128 
 int BNXT_AUTONEG_SPEED ; 
 int BNXT_DFLT_FW_RST_MAX_DSECS ; 
 int /*<<< orphan*/  BNXT_DFLT_FW_RST_MIN_DSECS ; 
 int /*<<< orphan*/  BNXT_FW_HEALTH_REG ; 
 int /*<<< orphan*/  BNXT_FW_HEARTBEAT_REG ; 
 int /*<<< orphan*/  BNXT_FW_RESET_CNT_REG ; 
 int /*<<< orphan*/  BNXT_FW_RESET_NOTIFY_SP_EVENT ; 
 int BNXT_GET_EVENT_PORT (int) ; 
 int /*<<< orphan*/  BNXT_HWRM_PF_UNLOAD_SP_EVENT ; 
 int /*<<< orphan*/  BNXT_HWRM_PORT_MODULE_SP_EVENT ; 
 int /*<<< orphan*/  BNXT_LINK_CHNG_SP_EVENT ; 
 int /*<<< orphan*/  BNXT_LINK_SPEED_CHNG_SP_EVENT ; 
 int /*<<< orphan*/  BNXT_PF (struct bnxt*) ; 
 int /*<<< orphan*/  BNXT_RESET_TASK_SILENT_SP_EVENT ; 
 int /*<<< orphan*/  BNXT_STATE_FW_FATAL_COND ; 
 int /*<<< orphan*/  BNXT_VF (struct bnxt*) ; 
 int /*<<< orphan*/  DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  EVENT_DATA1_RECOVERY_ENABLED (int) ; 
 int /*<<< orphan*/  EVENT_DATA1_RECOVERY_MASTER_FUNC (int) ; 
 int /*<<< orphan*/  EVENT_DATA1_RESET_NOTIFY_FATAL (int) ; 
 int HZ ; 
 int SPEED_UNKNOWN ; 
 void* bnxt_fw_health_readl (struct bnxt*,int /*<<< orphan*/ ) ; 
 int bnxt_fw_to_ethtool_speed (int) ; 
 int /*<<< orphan*/  bnxt_queue_sp_work (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_ulp_async_events (struct bnxt*,struct hwrm_async_event_cmpl*) ; 
 int /*<<< orphan*/  jiffies ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  netif_msg_drv (struct bnxt*) ; 
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
	case ASYNC_EVENT_CMPL_EVENT_ID_RESET_NOTIFY: {
		u32 data1 = le32_to_cpu(cmpl->event_data1);

		bp->fw_reset_timestamp = jiffies;
		bp->fw_reset_min_dsecs = cmpl->timestamp_lo;
		if (!bp->fw_reset_min_dsecs)
			bp->fw_reset_min_dsecs = BNXT_DFLT_FW_RST_MIN_DSECS;
		bp->fw_reset_max_dsecs = le16_to_cpu(cmpl->timestamp_hi);
		if (!bp->fw_reset_max_dsecs)
			bp->fw_reset_max_dsecs = BNXT_DFLT_FW_RST_MAX_DSECS;
		if (EVENT_DATA1_RESET_NOTIFY_FATAL(data1)) {
			netdev_warn(bp->dev, "Firmware fatal reset event received\n");
			set_bit(BNXT_STATE_FW_FATAL_COND, &bp->state);
		} else {
			netdev_warn(bp->dev, "Firmware non-fatal reset event received, max wait time %d msec\n",
				    bp->fw_reset_max_dsecs * 100);
		}
		set_bit(BNXT_FW_RESET_NOTIFY_SP_EVENT, &bp->sp_event);
		break;
	}
	case ASYNC_EVENT_CMPL_EVENT_ID_ERROR_RECOVERY: {
		struct bnxt_fw_health *fw_health = bp->fw_health;
		u32 data1 = le32_to_cpu(cmpl->event_data1);

		if (!fw_health)
			goto async_event_process_exit;

		fw_health->enabled = EVENT_DATA1_RECOVERY_ENABLED(data1);
		fw_health->master = EVENT_DATA1_RECOVERY_MASTER_FUNC(data1);
		if (!fw_health->enabled)
			break;

		if (netif_msg_drv(bp))
			netdev_info(bp->dev, "Error recovery info: error recovery[%d], master[%d], reset count[0x%x], health status: 0x%x\n",
				    fw_health->enabled, fw_health->master,
				    bnxt_fw_health_readl(bp,
							 BNXT_FW_RESET_CNT_REG),
				    bnxt_fw_health_readl(bp,
							 BNXT_FW_HEALTH_REG));
		fw_health->tmr_multiplier =
			DIV_ROUND_UP(fw_health->polling_dsecs * HZ,
				     bp->current_interval * 10);
		fw_health->tmr_counter = fw_health->tmr_multiplier;
		fw_health->last_fw_heartbeat =
			bnxt_fw_health_readl(bp, BNXT_FW_HEARTBEAT_REG);
		fw_health->last_fw_reset_cnt =
			bnxt_fw_health_readl(bp, BNXT_FW_RESET_CNT_REG);
		goto async_event_process_exit;
	}
	default:
		goto async_event_process_exit;
	}
	bnxt_queue_sp_work(bp);
async_event_process_exit:
	bnxt_ulp_async_events(bp, cmpl);
	return 0;
}