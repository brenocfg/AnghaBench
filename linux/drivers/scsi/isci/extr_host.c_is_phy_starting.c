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
struct TYPE_2__ {int current_state_id; } ;
struct isci_phy {TYPE_1__ sm; } ;
typedef  enum sci_phy_states { ____Placeholder_sci_phy_states } sci_phy_states ;

/* Variables and functions */
#define  SCI_PHY_STARTING 138 
#define  SCI_PHY_SUB_AWAIT_IAF_UF 137 
#define  SCI_PHY_SUB_AWAIT_OSSP_EN 136 
#define  SCI_PHY_SUB_AWAIT_SAS_POWER 135 
#define  SCI_PHY_SUB_AWAIT_SAS_SPEED_EN 134 
#define  SCI_PHY_SUB_AWAIT_SATA_PHY_EN 133 
#define  SCI_PHY_SUB_AWAIT_SATA_POWER 132 
#define  SCI_PHY_SUB_AWAIT_SATA_SPEED_EN 131 
#define  SCI_PHY_SUB_AWAIT_SIG_FIS_UF 130 
#define  SCI_PHY_SUB_FINAL 129 
#define  SCI_PHY_SUB_INITIAL 128 

__attribute__((used)) static bool is_phy_starting(struct isci_phy *iphy)
{
	enum sci_phy_states state;

	state = iphy->sm.current_state_id;
	switch (state) {
	case SCI_PHY_STARTING:
	case SCI_PHY_SUB_INITIAL:
	case SCI_PHY_SUB_AWAIT_SAS_SPEED_EN:
	case SCI_PHY_SUB_AWAIT_IAF_UF:
	case SCI_PHY_SUB_AWAIT_SAS_POWER:
	case SCI_PHY_SUB_AWAIT_SATA_POWER:
	case SCI_PHY_SUB_AWAIT_SATA_PHY_EN:
	case SCI_PHY_SUB_AWAIT_SATA_SPEED_EN:
	case SCI_PHY_SUB_AWAIT_OSSP_EN:
	case SCI_PHY_SUB_AWAIT_SIG_FIS_UF:
	case SCI_PHY_SUB_FINAL:
		return true;
	default:
		return false;
	}
}