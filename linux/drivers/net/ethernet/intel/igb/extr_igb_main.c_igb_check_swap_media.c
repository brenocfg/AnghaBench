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
struct TYPE_2__ {int media_type; } ;
struct e1000_hw {TYPE_1__ phy; } ;
struct igb_adapter {int copper_tries; int /*<<< orphan*/  netdev; int /*<<< orphan*/  flags; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_CONNSW ; 
 int E1000_CONNSW_AUTOSENSE_CONF ; 
 int E1000_CONNSW_AUTOSENSE_EN ; 
 int E1000_CONNSW_PHYSD ; 
 int E1000_CONNSW_PHY_PDN ; 
 int E1000_CONNSW_SERDESD ; 
 int /*<<< orphan*/  E1000_CTRL_EXT ; 
 int E1000_CTRL_EXT_LINK_MODE_PCIE_SERDES ; 
 int /*<<< orphan*/  IGB_FLAG_MEDIA_RESET ; 
#define  e1000_media_type_copper 130 
#define  e1000_media_type_fiber 129 
#define  e1000_media_type_internal_serdes 128 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void igb_check_swap_media(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 ctrl_ext, connsw;
	bool swap_now = false;

	ctrl_ext = rd32(E1000_CTRL_EXT);
	connsw = rd32(E1000_CONNSW);

	/* need to live swap if current media is copper and we have fiber/serdes
	 * to go to.
	 */

	if ((hw->phy.media_type == e1000_media_type_copper) &&
	    (!(connsw & E1000_CONNSW_AUTOSENSE_EN))) {
		swap_now = true;
	} else if ((hw->phy.media_type != e1000_media_type_copper) &&
		   !(connsw & E1000_CONNSW_SERDESD)) {
		/* copper signal takes time to appear */
		if (adapter->copper_tries < 4) {
			adapter->copper_tries++;
			connsw |= E1000_CONNSW_AUTOSENSE_CONF;
			wr32(E1000_CONNSW, connsw);
			return;
		} else {
			adapter->copper_tries = 0;
			if ((connsw & E1000_CONNSW_PHYSD) &&
			    (!(connsw & E1000_CONNSW_PHY_PDN))) {
				swap_now = true;
				connsw &= ~E1000_CONNSW_AUTOSENSE_CONF;
				wr32(E1000_CONNSW, connsw);
			}
		}
	}

	if (!swap_now)
		return;

	switch (hw->phy.media_type) {
	case e1000_media_type_copper:
		netdev_info(adapter->netdev,
			"MAS: changing media to fiber/serdes\n");
		ctrl_ext |=
			E1000_CTRL_EXT_LINK_MODE_PCIE_SERDES;
		adapter->flags |= IGB_FLAG_MEDIA_RESET;
		adapter->copper_tries = 0;
		break;
	case e1000_media_type_internal_serdes:
	case e1000_media_type_fiber:
		netdev_info(adapter->netdev,
			"MAS: changing media to copper\n");
		ctrl_ext &=
			~E1000_CTRL_EXT_LINK_MODE_PCIE_SERDES;
		adapter->flags |= IGB_FLAG_MEDIA_RESET;
		break;
	default:
		/* shouldn't get here during regular operation */
		netdev_err(adapter->netdev,
			"AMS: Invalid media type found, returning\n");
		break;
	}
	wr32(E1000_CTRL_EXT, ctrl_ext);
}