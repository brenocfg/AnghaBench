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
struct ksz_hw {int overrides; scalar_t__ io; } ;

/* Variables and functions */
 int FAST_AGING ; 
 scalar_t__ KS8842_SWITCH_CTRL_1_OFFSET ; 
 scalar_t__ KS8842_SWITCH_CTRL_2_OFFSET ; 
 scalar_t__ KS8842_SWITCH_CTRL_3_OFFSET ; 
 int /*<<< orphan*/  NO_EXC_COLLISION_DROP ; 
 int /*<<< orphan*/  SWITCH_AGGR_BACKOFF ; 
 int /*<<< orphan*/  SWITCH_AGING_ENABLE ; 
 int /*<<< orphan*/  SWITCH_FAST_AGING ; 
 int /*<<< orphan*/  SWITCH_FLOW_CTRL ; 
 int /*<<< orphan*/  SWITCH_LINK_AUTO_AGING ; 
 int /*<<< orphan*/  readw (scalar_t__) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sw_set_global_ctrl(struct ksz_hw *hw)
{
	u16 data;

	/* Enable switch MII flow control. */
	data = readw(hw->io + KS8842_SWITCH_CTRL_3_OFFSET);
	data |= SWITCH_FLOW_CTRL;
	writew(data, hw->io + KS8842_SWITCH_CTRL_3_OFFSET);

	data = readw(hw->io + KS8842_SWITCH_CTRL_1_OFFSET);

	/* Enable aggressive back off algorithm in half duplex mode. */
	data |= SWITCH_AGGR_BACKOFF;

	/* Enable automatic fast aging when link changed detected. */
	data |= SWITCH_AGING_ENABLE;
	data |= SWITCH_LINK_AUTO_AGING;

	if (hw->overrides & FAST_AGING)
		data |= SWITCH_FAST_AGING;
	else
		data &= ~SWITCH_FAST_AGING;
	writew(data, hw->io + KS8842_SWITCH_CTRL_1_OFFSET);

	data = readw(hw->io + KS8842_SWITCH_CTRL_2_OFFSET);

	/* Enable no excessive collision drop. */
	data |= NO_EXC_COLLISION_DROP;
	writew(data, hw->io + KS8842_SWITCH_CTRL_2_OFFSET);
}