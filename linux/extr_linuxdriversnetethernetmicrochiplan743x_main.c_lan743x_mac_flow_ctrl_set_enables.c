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
typedef  int /*<<< orphan*/  u32 ;
struct lan743x_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_FLOW ; 
 int /*<<< orphan*/  MAC_FLOW_CR_FCPT_MASK_ ; 
 int /*<<< orphan*/  MAC_FLOW_CR_RX_FCEN_ ; 
 int /*<<< orphan*/  MAC_FLOW_CR_TX_FCEN_ ; 
 int /*<<< orphan*/  lan743x_csr_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lan743x_mac_flow_ctrl_set_enables(struct lan743x_adapter *adapter,
					      bool tx_enable, bool rx_enable)
{
	u32 flow_setting = 0;

	/* set maximum pause time because when fifo space frees
	 * up a zero value pause frame will be sent to release the pause
	 */
	flow_setting = MAC_FLOW_CR_FCPT_MASK_;
	if (tx_enable)
		flow_setting |= MAC_FLOW_CR_TX_FCEN_;
	if (rx_enable)
		flow_setting |= MAC_FLOW_CR_RX_FCEN_;
	lan743x_csr_write(adapter, MAC_FLOW, flow_setting);
}