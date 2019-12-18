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
struct TYPE_6__ {int /*<<< orphan*/  opcode; } ;
struct control_phy {int phy_id; int sub_func; int port_type; int link_reset_retries; int /*<<< orphan*/  conn_handle; int /*<<< orphan*/  func_mask; int /*<<< orphan*/  speed_mask; int /*<<< orphan*/  hot_plug_delay; } ;
struct scb {TYPE_2__ header; struct control_phy control_phy; } ;
struct TYPE_7__ {int /*<<< orphan*/  role; } ;
struct asd_phy {TYPE_4__* phy_desc; TYPE_3__ sas_phy; } ;
struct asd_ascb {int /*<<< orphan*/  tasklet_complete; struct scb* scb; TYPE_1__* ha; } ;
struct TYPE_8__ {int flags; } ;
struct TYPE_5__ {struct asd_phy* phys; } ;

/* Variables and functions */
 int ASD_SATA_SPINUP_HOLD ; 
 int /*<<< orphan*/  CONTROL_PHY ; 
#define  ENABLE_PHY 130 
#define  EXECUTE_HARD_RESET 129 
 int /*<<< orphan*/  FUNCTION_MASK_DEFAULT ; 
 int /*<<< orphan*/  HOTPLUG_DELAY_TIMEOUT ; 
 int /*<<< orphan*/  PHY_ROLE_INITIATOR ; 
 int /*<<< orphan*/  PHY_ROLE_TARGET ; 
#define  RELEASE_SPINUP_HOLD 128 
 int SAS_PROTOCOL_ALL ; 
 int /*<<< orphan*/  SPINUP_HOLD_DIS ; 
 int /*<<< orphan*/  control_phy_tasklet_complete ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  set_speed_mask (int /*<<< orphan*/ *,TYPE_4__*) ; 

void asd_build_control_phy(struct asd_ascb *ascb, int phy_id, u8 subfunc)
{
	struct asd_phy *phy = &ascb->ha->phys[phy_id];
	struct scb *scb = ascb->scb;
	struct control_phy *control_phy = &scb->control_phy;

	scb->header.opcode = CONTROL_PHY;
	control_phy->phy_id = (u8) phy_id;
	control_phy->sub_func = subfunc;

	switch (subfunc) {
	case EXECUTE_HARD_RESET:  /* 0x81 */
	case ENABLE_PHY:          /* 0x01 */
		/* decide hot plug delay */
		control_phy->hot_plug_delay = HOTPLUG_DELAY_TIMEOUT;

		/* decide speed mask */
		set_speed_mask(&control_phy->speed_mask, phy->phy_desc);

		/* initiator port settings are in the hi nibble */
		if (phy->sas_phy.role == PHY_ROLE_INITIATOR)
			control_phy->port_type = SAS_PROTOCOL_ALL << 4;
		else if (phy->sas_phy.role == PHY_ROLE_TARGET)
			control_phy->port_type = SAS_PROTOCOL_ALL;
		else
			control_phy->port_type =
				(SAS_PROTOCOL_ALL << 4) | SAS_PROTOCOL_ALL;

		/* link reset retries, this should be nominal */
		control_phy->link_reset_retries = 10;
		/* fall through */

	case RELEASE_SPINUP_HOLD: /* 0x02 */
		/* decide the func_mask */
		control_phy->func_mask = FUNCTION_MASK_DEFAULT;
		if (phy->phy_desc->flags & ASD_SATA_SPINUP_HOLD)
			control_phy->func_mask &= ~SPINUP_HOLD_DIS;
		else
			control_phy->func_mask |= SPINUP_HOLD_DIS;
	}

	control_phy->conn_handle = cpu_to_le16(0xFFFF);

	ascb->tasklet_complete = control_phy_tasklet_complete;
}