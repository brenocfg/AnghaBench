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
struct ksz_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  hw_set_wol_frame (struct ksz_hw*,int,int,int const*,int /*<<< orphan*/ ,int const*) ; 

__attribute__((used)) static void hw_add_wol_bcast(struct ksz_hw *hw)
{
	static const u8 mask[] = { 0x3F };
	static const u8 pattern[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

	hw_set_wol_frame(hw, 2, 1, mask, ETH_ALEN, pattern);
}