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
struct TYPE_3__ {int /*<<< orphan*/  (* reset ) (struct igc_hw*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct igc_hw {TYPE_2__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct igc_hw*) ; 

__attribute__((used)) static inline s32 igc_reset_phy(struct igc_hw *hw)
{
	if (hw->phy.ops.reset)
		return hw->phy.ops.reset(hw);

	return 0;
}