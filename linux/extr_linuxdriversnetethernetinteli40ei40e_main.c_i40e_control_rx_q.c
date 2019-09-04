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
typedef  int u32 ;
struct i40e_hw {int dummy; } ;
struct i40e_pf {struct i40e_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_QRX_ENA (int) ; 
 int I40E_QRX_ENA_QENA_REQ_MASK ; 
 int I40E_QRX_ENA_QENA_REQ_SHIFT ; 
 int I40E_QRX_ENA_QENA_STAT_MASK ; 
 int I40E_QRX_ENA_QENA_STAT_SHIFT ; 
 int I40E_QTX_ENA_WAIT_COUNT ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void i40e_control_rx_q(struct i40e_pf *pf, int pf_q, bool enable)
{
	struct i40e_hw *hw = &pf->hw;
	u32 rx_reg;
	int i;

	for (i = 0; i < I40E_QTX_ENA_WAIT_COUNT; i++) {
		rx_reg = rd32(hw, I40E_QRX_ENA(pf_q));
		if (((rx_reg >> I40E_QRX_ENA_QENA_REQ_SHIFT) & 1) ==
		    ((rx_reg >> I40E_QRX_ENA_QENA_STAT_SHIFT) & 1))
			break;
		usleep_range(1000, 2000);
	}

	/* Skip if the queue is already in the requested state */
	if (enable == !!(rx_reg & I40E_QRX_ENA_QENA_STAT_MASK))
		return;

	/* turn on/off the queue */
	if (enable)
		rx_reg |= I40E_QRX_ENA_QENA_REQ_MASK;
	else
		rx_reg &= ~I40E_QRX_ENA_QENA_REQ_MASK;

	wr32(hw, I40E_QRX_ENA(pf_q), rx_reg);
}