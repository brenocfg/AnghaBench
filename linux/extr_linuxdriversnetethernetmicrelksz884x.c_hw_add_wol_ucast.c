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
typedef  int u8 ;
struct ksz_hw {int /*<<< orphan*/  override_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  hw_set_wol_frame (struct ksz_hw*,int /*<<< orphan*/ ,int,int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hw_add_wol_ucast(struct ksz_hw *hw)
{
	static const u8 mask[] = { 0x3F };

	hw_set_wol_frame(hw, 0, 1, mask, ETH_ALEN, hw->override_addr);
}