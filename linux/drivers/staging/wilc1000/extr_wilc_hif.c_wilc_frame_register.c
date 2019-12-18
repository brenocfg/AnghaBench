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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct wilc_vif {int /*<<< orphan*/  ndev; } ;
struct wilc_reg_frame {int reg; int /*<<< orphan*/  frame_type; int /*<<< orphan*/  reg_id; } ;
struct wid {int size; int /*<<< orphan*/ * val; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  reg_frame ;

/* Variables and functions */
#define  IEEE80211_STYPE_ACTION 129 
#define  IEEE80211_STYPE_PROBE_REQ 128 
 int /*<<< orphan*/  WID_REGISTER_FRAME ; 
 int /*<<< orphan*/  WID_STR ; 
 int /*<<< orphan*/  WILC_FW_ACTION_FRM_IDX ; 
 int /*<<< orphan*/  WILC_FW_PROBE_REQ_IDX ; 
 int /*<<< orphan*/  WILC_SET_CFG ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memset (struct wilc_reg_frame*,int,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int wilc_send_config_pkt (struct wilc_vif*,int /*<<< orphan*/ ,struct wid*,int) ; 

void wilc_frame_register(struct wilc_vif *vif, u16 frame_type, bool reg)
{
	struct wid wid;
	int result;
	struct wilc_reg_frame reg_frame;

	wid.id = WID_REGISTER_FRAME;
	wid.type = WID_STR;
	wid.size = sizeof(reg_frame);
	wid.val = (u8 *)&reg_frame;

	memset(&reg_frame, 0x0, sizeof(reg_frame));
	reg_frame.reg = reg;

	switch (frame_type) {
	case IEEE80211_STYPE_ACTION:
		reg_frame.reg_id = WILC_FW_ACTION_FRM_IDX;
		break;

	case IEEE80211_STYPE_PROBE_REQ:
		reg_frame.reg_id = WILC_FW_PROBE_REQ_IDX;
		break;

	default:
		break;
	}
	reg_frame.frame_type = cpu_to_le16(frame_type);
	result = wilc_send_config_pkt(vif, WILC_SET_CFG, &wid, 1);
	if (result)
		netdev_err(vif->ndev, "Failed to frame register\n");
}