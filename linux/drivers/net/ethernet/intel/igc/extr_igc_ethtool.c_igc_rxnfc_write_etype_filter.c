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
typedef  size_t u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_4__ {int etype; } ;
struct igc_nfc_filter {int action; size_t etype_reg_index; TYPE_2__ filter; } ;
struct igc_hw {int dummy; } ;
struct igc_adapter {int* etype_bitmap; TYPE_1__* pdev; struct igc_hw hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETHER_TYPE_FULL_MASK ; 
 int /*<<< orphan*/  IGC_ETQF (size_t) ; 
 int IGC_ETQF_ETYPE_MASK ; 
 int IGC_ETQF_FILTER_ENABLE ; 
 int IGC_ETQF_QUEUE_ENABLE ; 
 int IGC_ETQF_QUEUE_MASK ; 
 int IGC_ETQF_QUEUE_SHIFT ; 
 size_t MAX_ETYPE_FILTER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int ntohs (int) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int igc_rxnfc_write_etype_filter(struct igc_adapter *adapter,
					struct igc_nfc_filter *input)
{
	struct igc_hw *hw = &adapter->hw;
	u8 i;
	u32 etqf;
	u16 etype;

	/* find an empty etype filter register */
	for (i = 0; i < MAX_ETYPE_FILTER; ++i) {
		if (!adapter->etype_bitmap[i])
			break;
	}
	if (i == MAX_ETYPE_FILTER) {
		dev_err(&adapter->pdev->dev, "ethtool -N: etype filters are all used.\n");
		return -EINVAL;
	}

	adapter->etype_bitmap[i] = true;

	etqf = rd32(IGC_ETQF(i));
	etype = ntohs(input->filter.etype & ETHER_TYPE_FULL_MASK);

	etqf |= IGC_ETQF_FILTER_ENABLE;
	etqf &= ~IGC_ETQF_ETYPE_MASK;
	etqf |= (etype & IGC_ETQF_ETYPE_MASK);

	etqf &= ~IGC_ETQF_QUEUE_MASK;
	etqf |= ((input->action << IGC_ETQF_QUEUE_SHIFT)
		& IGC_ETQF_QUEUE_MASK);
	etqf |= IGC_ETQF_QUEUE_ENABLE;

	wr32(IGC_ETQF(i), etqf);

	input->etype_reg_index = i;

	return 0;
}