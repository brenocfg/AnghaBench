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
typedef  int uint32_t ;
struct mdp5_interface {scalar_t__ type; scalar_t__ mode; int num; } ;
struct mdp5_hw_mixer {int pp; } ;

/* Variables and functions */
 scalar_t__ INTF_DSI ; 
 scalar_t__ INTF_WB ; 
 scalar_t__ MDP5_INTF_DSI_MODE_COMMAND ; 
 int MDP5_IRQ_INTF0_VSYNC ; 
 int MDP5_IRQ_INTF1_VSYNC ; 
 int MDP5_IRQ_INTF2_VSYNC ; 
 int MDP5_IRQ_INTF3_VSYNC ; 
 int MDP5_IRQ_PING_PONG_0_RD_PTR ; 
 int MDP5_IRQ_WB_2_DONE ; 

__attribute__((used)) static inline uint32_t intf2vblank(struct mdp5_hw_mixer *mixer,
				   struct mdp5_interface *intf)
{
	/*
	 * In case of DSI Command Mode, the Ping Pong's read pointer IRQ
	 * acts as a Vblank signal. The Ping Pong buffer used is bound to
	 * layer mixer.
	 */

	if ((intf->type == INTF_DSI) &&
			(intf->mode == MDP5_INTF_DSI_MODE_COMMAND))
		return MDP5_IRQ_PING_PONG_0_RD_PTR << mixer->pp;

	if (intf->type == INTF_WB)
		return MDP5_IRQ_WB_2_DONE;

	switch (intf->num) {
	case 0:  return MDP5_IRQ_INTF0_VSYNC;
	case 1:  return MDP5_IRQ_INTF1_VSYNC;
	case 2:  return MDP5_IRQ_INTF2_VSYNC;
	case 3:  return MDP5_IRQ_INTF3_VSYNC;
	default: return 0;
	}
}