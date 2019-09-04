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
typedef  int u64 ;
typedef  int u32 ;
struct ixgb_tx_desc {int dummy; } ;
struct ixgb_hw {int dummy; } ;
struct TYPE_2__ {int dma; int count; } ;
struct ixgb_adapter {int tx_int_delay; int tx_cmd_type; scalar_t__ tx_int_delay_enable; struct ixgb_hw hw; TYPE_1__ tx_ring; } ;

/* Variables and functions */
 int IXGB_TCTL_TCE ; 
 int IXGB_TCTL_TPDE ; 
 int IXGB_TCTL_TXEN ; 
 int IXGB_TX_DESC_CMD_IDE ; 
 int IXGB_TX_DESC_TYPE ; 
 int /*<<< orphan*/  IXGB_WRITE_REG (struct ixgb_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TCTL ; 
 int /*<<< orphan*/  TDBAH ; 
 int /*<<< orphan*/  TDBAL ; 
 int /*<<< orphan*/  TDH ; 
 int /*<<< orphan*/  TDLEN ; 
 int /*<<< orphan*/  TDT ; 
 int /*<<< orphan*/  TIDV ; 

__attribute__((used)) static void
ixgb_configure_tx(struct ixgb_adapter *adapter)
{
	u64 tdba = adapter->tx_ring.dma;
	u32 tdlen = adapter->tx_ring.count * sizeof(struct ixgb_tx_desc);
	u32 tctl;
	struct ixgb_hw *hw = &adapter->hw;

	/* Setup the Base and Length of the Tx Descriptor Ring
	 * tx_ring.dma can be either a 32 or 64 bit value
	 */

	IXGB_WRITE_REG(hw, TDBAL, (tdba & 0x00000000ffffffffULL));
	IXGB_WRITE_REG(hw, TDBAH, (tdba >> 32));

	IXGB_WRITE_REG(hw, TDLEN, tdlen);

	/* Setup the HW Tx Head and Tail descriptor pointers */

	IXGB_WRITE_REG(hw, TDH, 0);
	IXGB_WRITE_REG(hw, TDT, 0);

	/* don't set up txdctl, it induces performance problems if configured
	 * incorrectly */
	/* Set the Tx Interrupt Delay register */

	IXGB_WRITE_REG(hw, TIDV, adapter->tx_int_delay);

	/* Program the Transmit Control Register */

	tctl = IXGB_TCTL_TCE | IXGB_TCTL_TXEN | IXGB_TCTL_TPDE;
	IXGB_WRITE_REG(hw, TCTL, tctl);

	/* Setup Transmit Descriptor Settings for this adapter */
	adapter->tx_cmd_type =
		IXGB_TX_DESC_TYPE |
		(adapter->tx_int_delay_enable ? IXGB_TX_DESC_CMD_IDE : 0);
}