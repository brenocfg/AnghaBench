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
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igb_adapter {int num_tx_queues; struct e1000_hw hw; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_I210_DTXMXPKTSZ ; 
 int /*<<< orphan*/  E1000_I210_TQAVCTRL ; 
 int /*<<< orphan*/  E1000_RXPBS ; 
 int E1000_TQAVCTRL_DATAFETCHARB ; 
 int E1000_TQAVCTRL_SP_WAIT_SR ; 
 int E1000_TQAVCTRL_XMIT_MODE ; 
 int /*<<< orphan*/  E1000_TXPBS ; 
 int I210_DTXMXPKTSZ_DEFAULT ; 
 int I210_RXPBSIZE_DEFAULT ; 
 int I210_RXPBSIZE_MASK ; 
 int I210_RXPBSIZE_PB_30KB ; 
 int I210_SR_QUEUES_NUM ; 
 int I210_TXPBSIZE_DEFAULT ; 
 int I210_TXPBSIZE_MASK ; 
 int I210_TXPBSIZE_PB0_8KB ; 
 int I210_TXPBSIZE_PB1_8KB ; 
 int I210_TXPBSIZE_PB2_4KB ; 
 int I210_TXPBSIZE_PB3_4KB ; 
 scalar_t__ e1000_i210 ; 
 int /*<<< orphan*/  igb_config_tx_modes (struct igb_adapter*,int) ; 
 scalar_t__ is_fqtss_enabled (struct igb_adapter*) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,char*) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void igb_setup_tx_mode(struct igb_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct e1000_hw *hw = &adapter->hw;
	u32 val;

	/* Only i210 controller supports changing the transmission mode. */
	if (hw->mac.type != e1000_i210)
		return;

	if (is_fqtss_enabled(adapter)) {
		int i, max_queue;

		/* Configure TQAVCTRL register: set transmit mode to 'Qav',
		 * set data fetch arbitration to 'round robin', set SP_WAIT_SR
		 * so SP queues wait for SR ones.
		 */
		val = rd32(E1000_I210_TQAVCTRL);
		val |= E1000_TQAVCTRL_XMIT_MODE | E1000_TQAVCTRL_SP_WAIT_SR;
		val &= ~E1000_TQAVCTRL_DATAFETCHARB;
		wr32(E1000_I210_TQAVCTRL, val);

		/* Configure Tx and Rx packet buffers sizes as described in
		 * i210 datasheet section 7.2.7.7.
		 */
		val = rd32(E1000_TXPBS);
		val &= ~I210_TXPBSIZE_MASK;
		val |= I210_TXPBSIZE_PB0_8KB | I210_TXPBSIZE_PB1_8KB |
			I210_TXPBSIZE_PB2_4KB | I210_TXPBSIZE_PB3_4KB;
		wr32(E1000_TXPBS, val);

		val = rd32(E1000_RXPBS);
		val &= ~I210_RXPBSIZE_MASK;
		val |= I210_RXPBSIZE_PB_30KB;
		wr32(E1000_RXPBS, val);

		/* Section 8.12.9 states that MAX_TPKT_SIZE from DTXMXPKTSZ
		 * register should not exceed the buffer size programmed in
		 * TXPBS. The smallest buffer size programmed in TXPBS is 4kB
		 * so according to the datasheet we should set MAX_TPKT_SIZE to
		 * 4kB / 64.
		 *
		 * However, when we do so, no frame from queue 2 and 3 are
		 * transmitted.  It seems the MAX_TPKT_SIZE should not be great
		 * or _equal_ to the buffer size programmed in TXPBS. For this
		 * reason, we set set MAX_ TPKT_SIZE to (4kB - 1) / 64.
		 */
		val = (4096 - 1) / 64;
		wr32(E1000_I210_DTXMXPKTSZ, val);

		/* Since FQTSS mode is enabled, apply any CBS configuration
		 * previously set. If no previous CBS configuration has been
		 * done, then the initial configuration is applied, which means
		 * CBS is disabled.
		 */
		max_queue = (adapter->num_tx_queues < I210_SR_QUEUES_NUM) ?
			    adapter->num_tx_queues : I210_SR_QUEUES_NUM;

		for (i = 0; i < max_queue; i++) {
			igb_config_tx_modes(adapter, i);
		}
	} else {
		wr32(E1000_RXPBS, I210_RXPBSIZE_DEFAULT);
		wr32(E1000_TXPBS, I210_TXPBSIZE_DEFAULT);
		wr32(E1000_I210_DTXMXPKTSZ, I210_DTXMXPKTSZ_DEFAULT);

		val = rd32(E1000_I210_TQAVCTRL);
		/* According to Section 8.12.21, the other flags we've set when
		 * enabling FQTSS are not relevant when disabling FQTSS so we
		 * don't set they here.
		 */
		val &= ~E1000_TQAVCTRL_XMIT_MODE;
		wr32(E1000_I210_TQAVCTRL, val);
	}

	netdev_dbg(netdev, "FQTSS %s\n", (is_fqtss_enabled(adapter)) ?
		   "enabled" : "disabled");
}