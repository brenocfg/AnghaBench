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
struct e1000_hw {int dummy; } ;
struct e1000_adapter {scalar_t__ en_mng_pt; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_MANC_ARP_EN ; 
 int /*<<< orphan*/  MANC ; 
 int /*<<< orphan*/  er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000_release_manageability(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;

	if (adapter->en_mng_pt) {
		u32 manc = er32(MANC);

		/* re-enable hardware interception of ARP */
		manc |= E1000_MANC_ARP_EN;

		ew32(MANC, manc);
	}
}