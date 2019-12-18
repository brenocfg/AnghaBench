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
struct ksz_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS8842_SWITCH_CTRL_7_OFFSET ; 
 int /*<<< orphan*/  SWITCH_UNK_DEF_PORT_ENABLE ; 
 int /*<<< orphan*/  sw_cfg (struct ksz_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void sw_cfg_unk_def_deliver(struct ksz_hw *hw, int set)
{
	sw_cfg(hw, KS8842_SWITCH_CTRL_7_OFFSET,
		SWITCH_UNK_DEF_PORT_ENABLE, set);
}