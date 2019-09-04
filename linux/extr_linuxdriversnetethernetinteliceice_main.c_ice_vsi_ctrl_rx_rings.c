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
struct ice_vsi {int num_rxq; int* rxq_map; int /*<<< orphan*/  idx; struct ice_pf* back; } ;
struct ice_hw {int dummy; } ;
struct ice_pf {TYPE_1__* pdev; struct ice_hw hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ICE_Q_WAIT_MAX_RETRY ; 
 int /*<<< orphan*/  QRX_CTRL (int) ; 
 int QRX_CTRL_QENA_REQ_M ; 
 int QRX_CTRL_QENA_REQ_S ; 
 int QRX_CTRL_QENA_STAT_M ; 
 int QRX_CTRL_QENA_STAT_S ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,char*) ; 
 int ice_pf_rxq_wait (struct ice_pf*,int,int) ; 
 int rd32 (struct ice_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wr32 (struct ice_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ice_vsi_ctrl_rx_rings(struct ice_vsi *vsi, bool ena)
{
	struct ice_pf *pf = vsi->back;
	struct ice_hw *hw = &pf->hw;
	int i, j, ret = 0;

	for (i = 0; i < vsi->num_rxq; i++) {
		int pf_q = vsi->rxq_map[i];
		u32 rx_reg;

		for (j = 0; j < ICE_Q_WAIT_MAX_RETRY; j++) {
			rx_reg = rd32(hw, QRX_CTRL(pf_q));
			if (((rx_reg >> QRX_CTRL_QENA_REQ_S) & 1) ==
			    ((rx_reg >> QRX_CTRL_QENA_STAT_S) & 1))
				break;
			usleep_range(1000, 2000);
		}

		/* Skip if the queue is already in the requested state */
		if (ena == !!(rx_reg & QRX_CTRL_QENA_STAT_M))
			continue;

		/* turn on/off the queue */
		if (ena)
			rx_reg |= QRX_CTRL_QENA_REQ_M;
		else
			rx_reg &= ~QRX_CTRL_QENA_REQ_M;
		wr32(hw, QRX_CTRL(pf_q), rx_reg);

		/* wait for the change to finish */
		ret = ice_pf_rxq_wait(pf, pf_q, ena);
		if (ret) {
			dev_err(&pf->pdev->dev,
				"VSI idx %d Rx ring %d %sable timeout\n",
				vsi->idx, pf_q, (ena ? "en" : "dis"));
			break;
		}
	}

	return ret;
}