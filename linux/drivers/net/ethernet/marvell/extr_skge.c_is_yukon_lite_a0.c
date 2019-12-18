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
struct skge_hw {scalar_t__ chip_id; } ;

/* Variables and functions */
 scalar_t__ B2_FAR ; 
 scalar_t__ CHIP_ID_YUKON ; 
 int /*<<< orphan*/  skge_read32 (struct skge_hw*,scalar_t__) ; 
 scalar_t__ skge_read8 (struct skge_hw*,scalar_t__) ; 
 int /*<<< orphan*/  skge_write32 (struct skge_hw*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skge_write8 (struct skge_hw*,scalar_t__,int) ; 

__attribute__((used)) static int is_yukon_lite_a0(struct skge_hw *hw)
{
	u32 reg;
	int ret;

	if (hw->chip_id != CHIP_ID_YUKON)
		return 0;

	reg = skge_read32(hw, B2_FAR);
	skge_write8(hw, B2_FAR + 3, 0xff);
	ret = (skge_read8(hw, B2_FAR + 3) != 0);
	skge_write32(hw, B2_FAR, reg);
	return ret;
}