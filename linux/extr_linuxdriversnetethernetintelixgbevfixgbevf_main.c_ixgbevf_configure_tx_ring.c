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
typedef  union ixgbe_adv_tx_desc {int dummy; } ixgbe_adv_tx_desc ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct ixgbevf_tx_buffer {int dummy; } ;
struct ixgbevf_ring {int dma; int count; int /*<<< orphan*/  state; int /*<<< orphan*/  tx_buffer_info; scalar_t__ next_to_use; scalar_t__ next_to_clean; scalar_t__ tail; int /*<<< orphan*/  reg_idx; } ;
struct ixgbe_hw {int dummy; } ;
struct ixgbevf_adapter {scalar_t__ io_addr; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int DMA_BIT_MASK (int) ; 
 int IXGBE_DCA_TXCTRL_DATA_RRO_EN ; 
 int IXGBE_DCA_TXCTRL_DESC_RRO_EN ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,scalar_t__) ; 
 int IXGBE_TXDCTL_ENABLE ; 
 int IXGBE_TXDCTL_SWFLSH ; 
 scalar_t__ IXGBE_VFDCA_TXCTRL (int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_VFTDBAH (int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_VFTDBAL (int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_VFTDH (int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_VFTDLEN (int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_VFTDT (int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_VFTDWBAH (int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_VFTDWBAL (int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_VFTXDCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,scalar_t__,int) ; 
 int /*<<< orphan*/  __IXGBEVF_HANG_CHECK_ARMED ; 
 int /*<<< orphan*/  __IXGBEVF_TX_XDP_RING_PRIMED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void ixgbevf_configure_tx_ring(struct ixgbevf_adapter *adapter,
				      struct ixgbevf_ring *ring)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u64 tdba = ring->dma;
	int wait_loop = 10;
	u32 txdctl = IXGBE_TXDCTL_ENABLE;
	u8 reg_idx = ring->reg_idx;

	/* disable queue to avoid issues while updating state */
	IXGBE_WRITE_REG(hw, IXGBE_VFTXDCTL(reg_idx), IXGBE_TXDCTL_SWFLSH);
	IXGBE_WRITE_FLUSH(hw);

	IXGBE_WRITE_REG(hw, IXGBE_VFTDBAL(reg_idx), tdba & DMA_BIT_MASK(32));
	IXGBE_WRITE_REG(hw, IXGBE_VFTDBAH(reg_idx), tdba >> 32);
	IXGBE_WRITE_REG(hw, IXGBE_VFTDLEN(reg_idx),
			ring->count * sizeof(union ixgbe_adv_tx_desc));

	/* disable head writeback */
	IXGBE_WRITE_REG(hw, IXGBE_VFTDWBAH(reg_idx), 0);
	IXGBE_WRITE_REG(hw, IXGBE_VFTDWBAL(reg_idx), 0);

	/* enable relaxed ordering */
	IXGBE_WRITE_REG(hw, IXGBE_VFDCA_TXCTRL(reg_idx),
			(IXGBE_DCA_TXCTRL_DESC_RRO_EN |
			 IXGBE_DCA_TXCTRL_DATA_RRO_EN));

	/* reset head and tail pointers */
	IXGBE_WRITE_REG(hw, IXGBE_VFTDH(reg_idx), 0);
	IXGBE_WRITE_REG(hw, IXGBE_VFTDT(reg_idx), 0);
	ring->tail = adapter->io_addr + IXGBE_VFTDT(reg_idx);

	/* reset ntu and ntc to place SW in sync with hardwdare */
	ring->next_to_clean = 0;
	ring->next_to_use = 0;

	/* In order to avoid issues WTHRESH + PTHRESH should always be equal
	 * to or less than the number of on chip descriptors, which is
	 * currently 40.
	 */
	txdctl |= (8 << 16);    /* WTHRESH = 8 */

	/* Setting PTHRESH to 32 both improves performance */
	txdctl |= (1u << 8) |    /* HTHRESH = 1 */
		   32;           /* PTHRESH = 32 */

	/* reinitialize tx_buffer_info */
	memset(ring->tx_buffer_info, 0,
	       sizeof(struct ixgbevf_tx_buffer) * ring->count);

	clear_bit(__IXGBEVF_HANG_CHECK_ARMED, &ring->state);
	clear_bit(__IXGBEVF_TX_XDP_RING_PRIMED, &ring->state);

	IXGBE_WRITE_REG(hw, IXGBE_VFTXDCTL(reg_idx), txdctl);

	/* poll to verify queue is enabled */
	do {
		usleep_range(1000, 2000);
		txdctl = IXGBE_READ_REG(hw, IXGBE_VFTXDCTL(reg_idx));
	}  while (--wait_loop && !(txdctl & IXGBE_TXDCTL_ENABLE));
	if (!wait_loop)
		hw_dbg(hw, "Could not enable Tx Queue %d\n", reg_idx);
}