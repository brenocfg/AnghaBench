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
struct ksz_hw_desc {int dummy; } ;
struct TYPE_2__ {int alloc; int size; } ;
struct ksz_hw {int tx_int_cnt; int tx_int_mask; TYPE_1__ tx_desc_info; TYPE_1__ rx_desc_info; } ;
struct dev_info {struct ksz_hw hw; } ;

/* Variables and functions */
 int DESC_ALIGNMENT ; 
 int NUM_OF_RX_DESC ; 
 int NUM_OF_TX_DESC ; 
 scalar_t__ ksz_alloc_desc (struct dev_info*) ; 
 int /*<<< orphan*/  ksz_check_desc_num (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_alert (char*) ; 

__attribute__((used)) static int ksz_alloc_mem(struct dev_info *adapter)
{
	struct ksz_hw *hw = &adapter->hw;

	/* Determine the number of receive and transmit descriptors. */
	hw->rx_desc_info.alloc = NUM_OF_RX_DESC;
	hw->tx_desc_info.alloc = NUM_OF_TX_DESC;

	/* Determine how many descriptors to skip transmit interrupt. */
	hw->tx_int_cnt = 0;
	hw->tx_int_mask = NUM_OF_TX_DESC / 4;
	if (hw->tx_int_mask > 8)
		hw->tx_int_mask = 8;
	while (hw->tx_int_mask) {
		hw->tx_int_cnt++;
		hw->tx_int_mask >>= 1;
	}
	if (hw->tx_int_cnt) {
		hw->tx_int_mask = (1 << (hw->tx_int_cnt - 1)) - 1;
		hw->tx_int_cnt = 0;
	}

	/* Determine the descriptor size. */
	hw->rx_desc_info.size =
		(((sizeof(struct ksz_hw_desc) + DESC_ALIGNMENT - 1) /
		DESC_ALIGNMENT) * DESC_ALIGNMENT);
	hw->tx_desc_info.size =
		(((sizeof(struct ksz_hw_desc) + DESC_ALIGNMENT - 1) /
		DESC_ALIGNMENT) * DESC_ALIGNMENT);
	if (hw->rx_desc_info.size != sizeof(struct ksz_hw_desc))
		pr_alert("Hardware descriptor size not right!\n");
	ksz_check_desc_num(&hw->rx_desc_info);
	ksz_check_desc_num(&hw->tx_desc_info);

	/* Allocate descriptors. */
	if (ksz_alloc_desc(adapter))
		return 1;

	return 0;
}