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
typedef  int /*<<< orphan*/  u16 ;
struct ksz_hw {scalar_t__ io; } ;

/* Variables and functions */
 scalar_t__ KS8841_WOL_CTRL_OFFSET ; 
 int /*<<< orphan*/  readw (scalar_t__) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hw_cfg_wol(struct ksz_hw *hw, u16 frame, int set)
{
	u16 data;

	data = readw(hw->io + KS8841_WOL_CTRL_OFFSET);
	if (set)
		data |= frame;
	else
		data &= ~frame;
	writew(data, hw->io + KS8841_WOL_CTRL_OFFSET);
}