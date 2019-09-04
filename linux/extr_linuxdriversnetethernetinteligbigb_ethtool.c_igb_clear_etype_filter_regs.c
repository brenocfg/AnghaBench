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
typedef  size_t u16 ;
struct e1000_hw {int dummy; } ;
struct igb_adapter {int* etype_bitmap; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ETQF (size_t) ; 
 int /*<<< orphan*/  E1000_ETQF_FILTER_ENABLE ; 
 int /*<<< orphan*/  E1000_ETQF_QUEUE_ENABLE ; 
 int /*<<< orphan*/  E1000_ETQF_QUEUE_MASK ; 
 int /*<<< orphan*/  rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igb_clear_etype_filter_regs(struct igb_adapter *adapter,
					u16 reg_index)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 etqf = rd32(E1000_ETQF(reg_index));

	etqf &= ~E1000_ETQF_QUEUE_ENABLE;
	etqf &= ~E1000_ETQF_QUEUE_MASK;
	etqf &= ~E1000_ETQF_FILTER_ENABLE;

	wr32(E1000_ETQF(reg_index), etqf);

	adapter->etype_bitmap[reg_index] = false;
}