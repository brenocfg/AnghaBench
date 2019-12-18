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
struct mdp5_pipeline {struct mdp5_interface* intf; } ;
struct mdp5_interface {int type; int /*<<< orphan*/  mode; } ;
struct mdp5_ctl {int /*<<< orphan*/  encoder_enabled; } ;

/* Variables and functions */
#define  INTF_DSI 129 
#define  INTF_WB 128 
 int /*<<< orphan*/  MDP5_INTF_DSI_MODE_COMMAND ; 

__attribute__((used)) static bool start_signal_needed(struct mdp5_ctl *ctl,
				struct mdp5_pipeline *pipeline)
{
	struct mdp5_interface *intf = pipeline->intf;

	if (!ctl->encoder_enabled)
		return false;

	switch (intf->type) {
	case INTF_WB:
		return true;
	case INTF_DSI:
		return intf->mode == MDP5_INTF_DSI_MODE_COMMAND;
	default:
		return false;
	}
}