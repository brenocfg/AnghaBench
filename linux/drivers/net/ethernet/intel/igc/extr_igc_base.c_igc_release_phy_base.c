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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* release_swfw_sync ) (struct igc_hw*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct igc_hw {TYPE_2__ mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_SWFW_PHY0_SM ; 
 int /*<<< orphan*/  stub1 (struct igc_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igc_release_phy_base(struct igc_hw *hw)
{
	u16 mask = IGC_SWFW_PHY0_SM;

	hw->mac.ops.release_swfw_sync(hw, mask);
}