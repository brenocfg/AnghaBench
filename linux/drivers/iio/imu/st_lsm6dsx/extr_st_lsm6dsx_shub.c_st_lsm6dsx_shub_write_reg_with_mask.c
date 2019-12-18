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
typedef  int /*<<< orphan*/  u8 ;
struct st_lsm6dsx_hw {int /*<<< orphan*/  page_lock; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int st_lsm6dsx_set_page (struct st_lsm6dsx_hw*,int) ; 

__attribute__((used)) static int
st_lsm6dsx_shub_write_reg_with_mask(struct st_lsm6dsx_hw *hw, u8 addr,
				    u8 mask, u8 val)
{
	int err;

	mutex_lock(&hw->page_lock);
	err = st_lsm6dsx_set_page(hw, true);
	if (err < 0)
		goto out;

	err = regmap_update_bits(hw->regmap, addr, mask, val);

	st_lsm6dsx_set_page(hw, false);
out:
	mutex_unlock(&hw->page_lock);

	return err;
}