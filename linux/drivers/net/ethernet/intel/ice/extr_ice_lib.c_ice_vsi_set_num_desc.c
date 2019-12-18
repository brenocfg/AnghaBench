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
struct ice_vsi {int type; TYPE_2__* back; int /*<<< orphan*/  num_tx_desc; int /*<<< orphan*/  num_rx_desc; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_DFLT_NUM_RX_DESC ; 
 int /*<<< orphan*/  ICE_DFLT_NUM_TX_DESC ; 
#define  ICE_VSI_LB 129 
#define  ICE_VSI_PF 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void ice_vsi_set_num_desc(struct ice_vsi *vsi)
{
	switch (vsi->type) {
	case ICE_VSI_PF:
		/* fall through */
	case ICE_VSI_LB:
		vsi->num_rx_desc = ICE_DFLT_NUM_RX_DESC;
		vsi->num_tx_desc = ICE_DFLT_NUM_TX_DESC;
		break;
	default:
		dev_dbg(&vsi->back->pdev->dev,
			"Not setting number of Tx/Rx descriptors for VSI type %d\n",
			vsi->type);
		break;
	}
}