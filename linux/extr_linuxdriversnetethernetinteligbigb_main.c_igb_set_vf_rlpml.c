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
struct e1000_hw {int dummy; } ;
struct igb_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_VMOLR (int) ; 
 int E1000_VMOLR_LPE ; 
 int E1000_VMOLR_RLPML_MASK ; 
 int MAX_JUMBO_FRAME_SIZE ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int igb_set_vf_rlpml(struct igb_adapter *adapter, int size,
				   int vfn)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 vmolr;

	if (size > MAX_JUMBO_FRAME_SIZE)
		size = MAX_JUMBO_FRAME_SIZE;

	vmolr = rd32(E1000_VMOLR(vfn));
	vmolr &= ~E1000_VMOLR_RLPML_MASK;
	vmolr |= size | E1000_VMOLR_LPE;
	wr32(E1000_VMOLR(vfn), vmolr);

	return 0;
}