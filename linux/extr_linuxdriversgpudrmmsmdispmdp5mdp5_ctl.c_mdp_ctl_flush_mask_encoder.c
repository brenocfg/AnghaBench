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
struct mdp5_interface {scalar_t__ type; int num; } ;

/* Variables and functions */
 scalar_t__ INTF_WB ; 
 int /*<<< orphan*/  MDP5_CTL_FLUSH_TIMING_0 ; 
 int /*<<< orphan*/  MDP5_CTL_FLUSH_TIMING_1 ; 
 int /*<<< orphan*/  MDP5_CTL_FLUSH_TIMING_2 ; 
 int /*<<< orphan*/  MDP5_CTL_FLUSH_TIMING_3 ; 
 int /*<<< orphan*/  MDP5_CTL_FLUSH_WB ; 

u32 mdp_ctl_flush_mask_encoder(struct mdp5_interface *intf)
{
	if (intf->type == INTF_WB)
		return MDP5_CTL_FLUSH_WB;

	switch (intf->num) {
	case 0: return MDP5_CTL_FLUSH_TIMING_0;
	case 1: return MDP5_CTL_FLUSH_TIMING_1;
	case 2: return MDP5_CTL_FLUSH_TIMING_2;
	case 3: return MDP5_CTL_FLUSH_TIMING_3;
	default: return 0;
	}
}