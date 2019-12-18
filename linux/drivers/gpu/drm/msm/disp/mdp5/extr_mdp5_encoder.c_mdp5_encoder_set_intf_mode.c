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
struct mdp5_interface {scalar_t__ type; int /*<<< orphan*/  mode; } ;
struct mdp5_encoder {struct mdp5_interface* intf; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 scalar_t__ INTF_DSI ; 
 int /*<<< orphan*/  MDP5_INTF_DSI_MODE_COMMAND ; 
 int /*<<< orphan*/  MDP5_INTF_DSI_MODE_VIDEO ; 
 int /*<<< orphan*/  MDP5_INTF_MODE_NONE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct mdp5_encoder* to_mdp5_encoder (struct drm_encoder*) ; 

void mdp5_encoder_set_intf_mode(struct drm_encoder *encoder, bool cmd_mode)
{
	struct mdp5_encoder *mdp5_encoder = to_mdp5_encoder(encoder);
	struct mdp5_interface *intf = mdp5_encoder->intf;

	/* TODO: Expand this to set writeback modes too */
	if (cmd_mode) {
		WARN_ON(intf->type != INTF_DSI);
		intf->mode = MDP5_INTF_DSI_MODE_COMMAND;
	} else {
		if (intf->type == INTF_DSI)
			intf->mode = MDP5_INTF_DSI_MODE_VIDEO;
		else
			intf->mode = MDP5_INTF_MODE_NONE;
	}
}