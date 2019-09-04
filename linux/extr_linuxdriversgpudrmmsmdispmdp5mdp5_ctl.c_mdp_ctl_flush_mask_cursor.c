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

/* Variables and functions */
 int /*<<< orphan*/  MDP5_CTL_FLUSH_CURSOR_0 ; 
 int /*<<< orphan*/  MDP5_CTL_FLUSH_CURSOR_1 ; 

u32 mdp_ctl_flush_mask_cursor(int cursor_id)
{
	switch (cursor_id) {
	case 0: return MDP5_CTL_FLUSH_CURSOR_0;
	case 1: return MDP5_CTL_FLUSH_CURSOR_1;
	default: return 0;
	}
}